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

FROM incubus/devel
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

ADD sim /root/sim

ADD ycm_extra_conf.py /root/sim/.ycm_extra_conf.py

RUN cd $HOME/sim && \
    cmake . && \
    make -j 4 
    
