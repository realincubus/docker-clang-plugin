#!/bin/bash
docker run --privileged -d --name sim_devel incubus/devel_sim /bin/bash -c 'while :; do echo "Hit CTRL+C"; sleep 1; done'
