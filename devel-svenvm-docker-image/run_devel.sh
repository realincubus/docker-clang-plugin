#!/bin/bash
docker run --privileged -d --name svenvm_devel incubus/devel_svenvm /bin/bash -c 'while :; do echo "Hit CTRL+C"; sleep 1; done'
