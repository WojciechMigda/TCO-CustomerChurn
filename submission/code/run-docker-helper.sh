#!/bin/sh

docker run --shm-size 4G \
  -v /repo/tco-customerchurn/data:/data:ro \
  -v /repo/tco-customerchurn-docker/submission/code/docker-out:/workdir \
  tco-churn ./test.sh /data /workdir
