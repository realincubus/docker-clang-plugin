#!/bin/bash
docker run --privileged -d --name ttt_devel incubus/devel_ttt /bin/bash -c 'while :; do echo "Hit CTRL+C"; sleep 1; done'
