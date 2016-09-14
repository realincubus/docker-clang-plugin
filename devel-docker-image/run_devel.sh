#!/bin/bash
docker run -d --name plugin_devel incubus/devel /bin/bash -c 'while :; do echo "Hit CTRL+C"; sleep 1; done'
