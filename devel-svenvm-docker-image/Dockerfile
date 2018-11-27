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

ADD SimulationVM /root/SimulationVM

ADD ycm_extra_conf.py /root/SimulationVM/.ycm_extra_conf.py

RUN cd $HOME/SimulationVM && \
    cmake . && \
    make -j 4 
    
