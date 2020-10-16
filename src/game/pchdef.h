//add here most rarely modified headers to speed up debug build compilation
#pragma once
#include "Policies/SingletonImp.h"
#include "WorldSocket.h"                                    // must be first to make ACE happy with ACE includes in it
#include "Common.h"

#include "Dynamic/FactoryHolder.h"
#include "Dynamic/ObjectRegistry.h"
#include "MapManager.h"
#include "Log.h"
#include "ObjectAccessor.h"
#include "ObjectGuid.h"
#include "SQLStorages.h"
#include "Opcodes.h"
#include "SharedDefines.h"
#include "GuildMgr.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"

//#error ("awda")
