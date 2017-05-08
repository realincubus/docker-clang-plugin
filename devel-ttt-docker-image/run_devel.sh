#!/bin/bash
docker run --privileged -d --name ttt_devel incubus/devel-ttt /bin/bash -c 'while :; do echo "Hit CTRL+C"; sleep 1; done'
