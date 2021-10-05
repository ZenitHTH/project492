#!/bin/bash

docker network create --subnet=10.10.0.0/24 --gateway=10.10.0.1 internal
docker build -t mysqlproject:test ./mysql
docker build -t pymqttproject:test ./python
docker pull metabase/metabase
docker run -d --net internal --net-alias mysql --name mysqlproject mysqlproject:test
docker run -d --net internal --net-alias pymqtt --name pymqttproject pymqttproject:test
docker run -d --net internal --net-alias metabase -p 3000:3000 --name metabase metabase/metabase

