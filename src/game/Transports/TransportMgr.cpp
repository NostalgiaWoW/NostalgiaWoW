/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "TransportMgr.h"
#include "Transport.h"
#include "MoveSpline.h"
#include "MapManager.h"
#include "ObjectMgr.h"
#include "MoveMap.h"

TransportTemplate::~TransportTemplate()
{
    // Collect shared pointers into a set to avoid deleting the same memory more than once
    std::set<TransportSpline*> splines;
    for (size_t i = 0; i < keyFrames.size(); ++i)
        splines.insert(keyFrames[i].Spline);

    for (std::set<TransportSpline*>::iterator itr = splines.begin(); itr != splines.end(); ++itr)
        delete *itr;
}

TransportMgr::TransportMgr() { }

TransportMgr::~TransportMgr() { }

void TransportMgr::Unload()
{
    _transportTemplates.clear();
}

void TransportMgr::LoadTransportTemplates()
{
    uint32 oldMSTime = WorldTimer::getMSTime();

    QueryResult* result = WorldDatabase.Query("SELECT entry FROM gameobject_template WHERE type = 15 ORDER BY entry ASC");

    if (!result)
    {
        sLog.outString(">> Loaded 0 transport templates. DB table `gameobject_template` has no transports!");
        return;
    }

    uint32 count = 0;

    do
    {
        Field* fields = result->Fetch();
        uint32 entry = fields[0].GetUInt32();
        GameObjectInfo const* goInfo = ObjectMgr::GetGameObjectInfo(entry);
        if (goInfo == NULL)
        {
            sLog.outErrorDb("Transport %u has no associated GameObjectTemplate from `gameobject_template` , skipped.", entry);
            continue;
        }

        if (goInfo->moTransport.taxiPathId >= sTaxiPathNodesByPath.size())
        {
            sLog.outErrorDb("Transport %u (name: %s) has an invalid path specified in `gameobject_template`.`data0` (%u) field, skipped.", entry, goInfo->name, goInfo->moTransport.taxiPathId);
            continue;
        }

        // paths are generated per template, saves us from generating it again in case of instanced transports
        TransportTemplate& transport = _transportTemplates[entry];
        transport.entry = entry;
        GeneratePath(goInfo, &transport);
        MMAP::MMapFactory::createOrGetMMapManager()->loadGameObject(goInfo->displayId);

        // transports in instance are only on one map
        if (transport.inInstance)
            _instanceTransports[*transport.mapsUsed.begin()].insert(entry);

        ++count;
    }
    while (result->NextRow());

    delete result;
    sLog.outString(">> Loaded %u transport templates in %u ms", count, WorldTimer::getMSTimeDiffToNow(oldMSTime));
}

class SplineRawInitializer
{
public:
    SplineRawInitializer(Movement::PointsArray& points) : _points(points) { }

    void operator()(uint8& mode, bool& cyclic, Movement::PointsArray& points, int& lo, int& hi) const
    {
        mode = Movement::SplineBase::ModeCatmullrom;
        cyclic = false;
        points.assign(_points.begin(), _points.end());
        lo = 1;
        hi = points.size() - 2;
    }

    Movement::PointsArray& _points;
};

void TransportMgr::GeneratePath(GameObjectInfo const* goInfo, TransportTemplate* transport)
{
    uint32 pathId = goInfo->moTransport.taxiPathId;
    TaxiPathNodeList const& path = sTaxiPathNodesByPath[pathId];
    std::vector<KeyFrame>& keyFrames = transport->keyFrames;
    Movement::PointsArray splinePath, allPoints;
    bool mapChange = false;
    for (size_t i = 0; i < path.size(); ++i)
        allPoints.push_back(G3D::Vector3(path[i].x, path[i].y, path[i].z));

    // Add extra points to allow derivative calculations for all path nodes
    allPoints.insert(allPoints.begin(), allPoints.front().lerp(allPoints[1], -0.2f));
    allPoints.push_back(allPoints.back().lerp(allPoints[allPoints.size() - 2], -0.2f));
    allPoints.push_back(allPoints.back().lerp(allPoints[allPoints.size() - 2], -1.0f));

    SplineRawInitializer initer(allPoints);
    TransportSpline orientationSpline;
    orientationSpline.init_spline_custom(initer);
    orientationSpline.initLengths();

    for (size_t i = 1; i < path.size() - 1; ++i)
    {
        if (!mapChange)
        {
            TaxiPathNodeEntry const& node_i = path[i];
            if (i != path.size() - 1 && (node_i.actionFlag & 1 || node_i.mapid != path[i + 1].mapid))
            {
                keyFrames.back().Teleport = true;
                mapChange = true;
            }
            else
            {
                KeyFrame k(node_i);
                G3D::Vector3 h;
                orientationSpline.evaluate_derivative(i + 1, 0.0f, h);
                k.InitialOrientation = MapManager::NormalizeOrientation(atan2(h.y, h.x) + M_PI);

                keyFrames.push_back(k);
                splinePath.push_back(G3D::Vector3(node_i.x, node_i.y, node_i.z));
                transport->mapsUsed.insert(k.Node->mapid);
            }
        }
        else
            mapChange = false;
    }

    ASSERT(!keyFrames.empty());

    if (transport->mapsUsed.size() > 1)
    {
        for (std::set<uint32>::const_iterator itr = transport->mapsUsed.begin(); itr != transport->mapsUsed.end(); ++itr)
            ASSERT(!sMapStorage.LookupEntry<MapEntry>(*itr)->Instanceable());

        transport->inInstance = false;
    }
    else
        transport->inInstance = sMapStorage.LookupEntry<MapEntry>(*transport->mapsUsed.begin())->Instanceable();

    // last to first is always "teleport", even for closed paths
    keyFrames.back().Teleport = true;

    const float speed = float(goInfo->moTransport.moveSpeed);
    const float accel = float(goInfo->moTransport.accelRate);
    const float accel_dist = 0.5f * speed * speed / accel;

    transport->accelTime = speed / accel;
    transport->accelDist = accel_dist;

    int32 firstStop = -1;
    int32 lastStop = -1;

    // first cell is arrived at by teleportation :S
    keyFrames[0].DistFromPrev = 0;
    keyFrames[0].Index = 1;
    if (keyFrames[0].IsStopFrame())
    {
        firstStop = 0;
        lastStop = 0;
    }

    // find the rest of the distances between key points
    // Every path segment has its own spline
    size_t start = 0;
    for (size_t i = 1; i < keyFrames.size(); ++i)
    {
        if (keyFrames[i - 1].Teleport || i + 1 == keyFrames.size())
        {
            size_t extra = !keyFrames[i - 1].Teleport ? 1 : 0;
            TransportSpline* spline = new TransportSpline();
            spline->init_spline(&splinePath[start], i - start + extra, Movement::SplineBase::ModeCatmullrom);
            spline->initLengths();
            for (size_t j = start; j < i + extra; ++j)
            {
                keyFrames[j].Index = j - start + 1;
                keyFrames[j].DistFromPrev = spline->length(j - start, j + 1 - start);
                if (j > 0)
                    keyFrames[j - 1].NextDistFromPrev = keyFrames[j].DistFromPrev;
                keyFrames[j].Spline = spline;
            }

            if (keyFrames[i - 1].Teleport)
            {
                keyFrames[i].Index = i - start + 1;
                keyFrames[i].DistFromPrev = 0.0f;
                keyFrames[i - 1].NextDistFromPrev = 0.0f;
                keyFrames[i].Spline = spline;
            }

            start = i;
        }

        if (keyFrames[i].IsStopFrame())
        {
            // remember first stop frame
            if (firstStop == -1)
                firstStop = i;
            lastStop = i;
        }
    }

    keyFrames.back().NextDistFromPrev = keyFrames.front().DistFromPrev;

    if (firstStop == -1 || lastStop == -1)
        firstStop = lastStop = 0;

    // at stopping keyframes, we define distSinceStop == 0,
    // and distUntilStop is to the next stopping keyframe.
    // this is required to properly handle cases of two stopping frames in a row (yes they do exist)
    float tmpDist = 0.0f;
    for (size_t i = 0; i < keyFrames.size(); ++i)
    {
        int32 j = (i + lastStop) % keyFrames.size();
        if (keyFrames[j].IsStopFrame() || j == lastStop)
            tmpDist = 0.0f;
        else
            tmpDist += keyFrames[j].DistFromPrev;
        keyFrames[j].DistSinceStop = tmpDist;
    }

    tmpDist = 0.0f;
    for (int32 i = int32(keyFrames.size()) - 1; i >= 0; i--)
    {
        int32 j = (i + firstStop) % keyFrames.size();
        tmpDist += keyFrames[(j + 1) % keyFrames.size()].DistFromPrev;
        keyFrames[j].DistUntilStop = tmpDist;
        if (keyFrames[j].IsStopFrame() || j == firstStop)
            tmpDist = 0.0f;
    }

    for (size_t i = 0; i < keyFrames.size(); ++i)
    {
        float total_dist = keyFrames[i].DistSinceStop + keyFrames[i].DistUntilStop;
        if (total_dist < 2 * accel_dist) // won't reach full speed
        {
            if (keyFrames[i].DistSinceStop < keyFrames[i].DistUntilStop) // is still accelerating
            {
                // calculate accel+brake time for this short segment
                float segment_time = 2.0f * sqrt((keyFrames[i].DistUntilStop + keyFrames[i].DistSinceStop) / accel);
                // substract acceleration time
                keyFrames[i].TimeTo = segment_time - sqrt(2 * keyFrames[i].DistSinceStop / accel);
            }
            else // slowing down
                keyFrames[i].TimeTo = sqrt(2 * keyFrames[i].DistUntilStop / accel);
        }
        else if (keyFrames[i].DistSinceStop < accel_dist) // still accelerating (but will reach full speed)
        {
            // calculate accel + cruise + brake time for this long segment
            float segment_time = (keyFrames[i].DistUntilStop + keyFrames[i].DistSinceStop) / speed + (speed / accel);
            // substract acceleration time
            keyFrames[i].TimeTo = segment_time - sqrt(2 * keyFrames[i].DistSinceStop / accel);
        }
        else if (keyFrames[i].DistUntilStop < accel_dist) // already slowing down (but reached full speed)
            keyFrames[i].TimeTo = sqrt(2 * keyFrames[i].DistUntilStop / accel);
        else // at full speed
            keyFrames[i].TimeTo = (keyFrames[i].DistUntilStop / speed) + (0.5f * speed / accel);
    }

    // calculate tFrom times from tTo times
    float segmentTime = 0.0f;
    for (size_t i = 0; i < keyFrames.size(); ++i)
    {
        int32 j = (i + lastStop) % keyFrames.size();
        if (keyFrames[j].IsStopFrame() || j == lastStop)
            segmentTime = keyFrames[j].TimeTo;
        keyFrames[j].TimeFrom = segmentTime - keyFrames[j].TimeTo;
    }

    // calculate path times
    keyFrames[0].ArriveTime = 0;
    float curPathTime = 0.0f;
    if (keyFrames[0].IsStopFrame())
    {
        curPathTime = float(keyFrames[0].Node->delay);
        keyFrames[0].DepartureTime = uint32(curPathTime * IN_MILLISECONDS);
    }

    for (size_t i = 1; i < keyFrames.size(); ++i)
    {
        curPathTime += keyFrames[i - 1].TimeTo;
        if (keyFrames[i].IsStopFrame())
        {
            keyFrames[i].ArriveTime = uint32(curPathTime * IN_MILLISECONDS);
            keyFrames[i - 1].NextArriveTime = keyFrames[i].ArriveTime;
            curPathTime += float(keyFrames[i].Node->delay);
            keyFrames[i].DepartureTime = uint32(curPathTime * IN_MILLISECONDS);
        }
        else
        {
            curPathTime -= keyFrames[i].TimeTo;
            keyFrames[i].ArriveTime = uint32(curPathTime * IN_MILLISECONDS);
            keyFrames[i - 1].NextArriveTime = keyFrames[i].ArriveTime;
            keyFrames[i].DepartureTime = keyFrames[i].ArriveTime;
        }
    }

    keyFrames.back().NextArriveTime = keyFrames.back().DepartureTime;
    // the client destroys a transport by itself after a while, refresh is needed mid course
    // Feathermoon 303 & Teldrassil 293 ferries
    if (pathId == 303 || pathId == 293)
        keyFrames[12].Update = true;
    transport->pathTime = keyFrames.back().DepartureTime;
}

Transport* TransportMgr::CreateTransport(uint32 entry, uint32 guid /*= 0*/, Map* map /*= NULL*/)
{
    // instance case, execute GetGameObjectEntry hook
    if (map && !entry)
        return NULL;

    TransportTemplate const* tInfo = GetTransportTemplate(entry);
    if (!tInfo)
    {
        sLog.outErrorDb("Transport %u will not be loaded, `transport_template` missing", entry);
        return NULL;
    }

    // create transport...
    Transport* trans = new Transport();

    // ...at first waypoint
    TaxiPathNodeEntry const* startNode = tInfo->keyFrames.begin()->Node;
    uint32 mapId = startNode->mapid;
    float x = startNode->x;
    float y = startNode->y;
    float z = startNode->z;
    float o = tInfo->keyFrames.begin()->InitialOrientation;

    // initialize the gameobject base
    // HIGHGUID_MO_TRANSPORT
    uint32 guidLow = guid ? guid : map->GenerateLocalLowGuid(HIGHGUID_MO_TRANSPORT);
    if (!trans->Create(guidLow, entry, mapId, x, y, z, o, 255))
    {
        delete trans;
        return NULL;
    }

    if (MapEntry const* mapEntry = sMapStorage.LookupEntry<MapEntry>(mapId))
    {
        if (mapEntry->Instanceable() != tInfo->inInstance)
        {
            sLog.outError("Transport %u (name: %s) attempted creation in instance map (id: %u) but it is not an instanced transport!", entry, trans->GetName(), mapId);
            delete trans;
            return NULL;
        }
    }

    // use preset map for instances (need to know which instance)
    trans->SetLocationInstanceId(sMapMgr.GetContinentInstanceId(mapId, x, y));
    trans->SetMap(map ? map : sMapMgr.CreateMap(mapId, trans));

    // Passengers will be loaded once a player is near
    trans->GetMap()->Add<Transport>(trans);
    return trans;
}

void TransportMgr::SpawnContinentTransports()
{
    if (_transportTemplates.empty())
        return;

    uint32 oldMSTime = WorldTimer::getMSTime();

    QueryResult* result = WorldDatabase.Query("SELECT guid, entry FROM transports");

    uint32 count = 0;
    if (result)
    {
        do
        {
            Field* fields = result->Fetch();
            uint32 guid = fields[0].GetUInt32();
            uint32 entry = fields[1].GetUInt32();

            if (TransportTemplate const* tInfo = GetTransportTemplate(entry))
                if (!tInfo->inInstance)
                    if (CreateTransport(entry, guid))
                        ++count;

        }
        while (result->NextRow());
        delete result;
    }

    sLog.outString(">> Spawned %u continent transports in %u ms", count, WorldTimer::getMSTimeDiffToNow(oldMSTime));
}

void TransportMgr::CreateInstanceTransports(Map* map)
{
    TransportInstanceMap::const_iterator mapTransports = _instanceTransports.find(map->GetId());

    // no transports here
    if (mapTransports == _instanceTransports.end() || mapTransports->second.empty())
        return;

    // create transports
    for (std::set<uint32>::const_iterator itr = mapTransports->second.begin(); itr != mapTransports->second.end(); ++itr)
        CreateTransport(*itr, 0, map);
}
