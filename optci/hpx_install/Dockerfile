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


FROM incubus/optci
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# Update and force a refresh of all package lists even if they appear up to date.
RUN pacman -Syy --noconfirm && \ 
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -Syu pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm --force -S jemalloc wget && \
    pacman --noconfirm --force -Scc 

# todo need jemalloc
RUN cd ~ && \
    git clone https://github.com/STEllAR-GROUP/hpx.git && \
    cd hpx && \
    mkdir build && \
    cd build && \
    cmake -D CMAKE_CXX_STANDARD=14 -DHPX_WITH_MALLOC=jemalloc .. 

RUN cd ~/hpx/build && \
    make -j 10

RUN cd ~/hpx/build && \
    make install

