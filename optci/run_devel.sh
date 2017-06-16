#!/bin/bash
docker run --privileged -d --name optci_devel incubus/optci /bin/bash -c 'while :; do echo "Hit CTRL+C"; sleep 1; done'
