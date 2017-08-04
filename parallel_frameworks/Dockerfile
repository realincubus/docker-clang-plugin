############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang

FROM incubus/gcc
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

RUN pacman -Syy --noconfirm && \ 
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -Syu pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm --force -S hwloc jemalloc wget boost && \
    pacman --noconfirm --force -Scc 

RUN cd ~ && \
    git clone --depth=1 https://github.com/STEllAR-GROUP/hpx.git && \
    cd hpx && \
    mkdir build && \
    cd build && \
    cmake -D CMAKE_CXX_STANDARD=14 -DCMAKE_INSTALL_PREFIX=/usr/ -DHPX_WITH_MALLOC=jemalloc .. && \
    make -j 24 && \
    make install && \
    cd ~ && \
    rm -rf hpx

