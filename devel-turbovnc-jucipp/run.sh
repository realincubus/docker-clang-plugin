#!/bin/bash
user=$(whoami)
uid=$(id -u $user)
gid=$(id -g $user)
pw=12345678
docker run \
           --rm \
           -p 5902:5901 \
           --name turbo-jucipp \
           -v /home/$user/share:/home/$user/share\
           -e user=$user\
           -e uid=$uid \
           -e gid=$gid \
           -e pw=$pw\
          incubus/devel-turbovnc-jucipp /bin/bash -c "/turboscript_jucipp"
