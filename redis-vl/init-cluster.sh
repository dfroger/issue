#!/bin/bash

docker compose exec -it redis-1 redis-cli --cluster create \
  redis-1:6379 redis-2:6379 redis-3:6379 \
  --cluster-replicas 0 \
  --cluster-yes
