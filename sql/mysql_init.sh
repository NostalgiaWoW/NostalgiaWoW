#!/bin/bash

create_mysql=${DRONE_WORKSPACE}/sql/create/create_mysql.sql

logs_database=${DRONE_WORKSPACE}/sql/base/logs.sql
logon_database=${DRONE_WORKSPACE}/sql/base/logon.sql
characters_database=${DRONE_WORKSPACE}/sql/base/characters.sql
world_database=${DRONE_WORKSPACE}/sql/base/world.sql

echo "$0: running $create_mysql";         "${mysql[@]}" < "$create_mysql"; echo

echo "$0: running $logs_database";        "${mysql[@]}" logs < "$logs_database"; echo
echo "$0: running $logon_database";       "${mysql[@]}" logon < "$logon_database"; echo
echo "$0: running $characters_database";  "${mysql[@]}" characters < "$characters_database"; echo
echo "$0: running $world_database";       "${mysql[@]}" world < "$world_database"; echo
