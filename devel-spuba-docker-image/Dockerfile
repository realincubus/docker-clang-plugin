############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang
#     ├─incubus/pet
#       ├─incubus/pluto
#         ├─incubus/plugin
#           ├─incubus/ycm
#             ├─incubus/devel

FROM compus.physik.uni-greifswald.de:5000/kemnitzs/devel
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

RUN pacman --noconfirm --force -Sy  boost && \
    pacman --noconfirm --force -Scc 

ADD spuba /root/spuba

ADD ycm_extra_conf.py $HOME/spuba/.ycm_extra_conf.py

RUN cd $HOME/spuba && \
    cmake . && \
    make -j 4 
    
