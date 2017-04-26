#!/bin/bash
user=$(whoami)
uid=$(id -u $user)
gid=$(id -g $user)
pw=12345678
docker run \
           --rm \
           -p 5901:5901 \
           --name turbodocker \
           -v /home/$user/share:/home/$user/share\
           -e user=$user\
           -e uid=$uid \
           -e gid=$gid \
           -e pw=$pw\
          incubus/devel-turbovnc /bin/bash -c "/turboscript"
