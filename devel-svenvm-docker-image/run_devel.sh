#!/bin/bash
docker run --privileged -d --name svenvm_devel incubus/devel-svenvm /bin/bash -c 'while :; do echo "Hit CTRL+C"; sleep 1; done'
