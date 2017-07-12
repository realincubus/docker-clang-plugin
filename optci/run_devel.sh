#!/bin/bash
docker run --privileged --device /dev/nvidia0:/dev/nvidia0 --device /dev/nvidiactl:/dev/nvidiactl --device /dev/nvidia-uvm:/dev/nvidia-uvm -d --name optci_devel -v $PWD/share:/share incubus/optci /bin/bash -c 'while :; do echo "Hit CTRL+C"; sleep 1; done'
