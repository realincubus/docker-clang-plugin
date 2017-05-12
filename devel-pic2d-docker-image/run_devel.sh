#!/bin/bash
docker run --privileged -d --name pic_devel incubus/devel-pic2d /bin/bash -c 'while :; do echo "Hit CTRL+C"; sleep 1; done'
