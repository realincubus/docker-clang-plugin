#!/bin/bash
docker run --privileged -d --name optci_devel -v $PWD/share:/share incubus/optci /bin/bash -c 'while :; do echo "Hit CTRL+C"; sleep 1; done'
