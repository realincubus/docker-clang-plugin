#!/bin/bash
docker run --privileged -d --name spuba_devel incubus/devel-spuba /bin/bash -c 'while :; do echo "Hit CTRL+C"; sleep 1; done'
