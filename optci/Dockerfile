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


FROM incubus/devel-pic2d
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# Update and force a refresh of all package lists even if they appear up to date.
RUN pacman -Syy --noconfirm && \ 
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -Syu pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm --force -S bc perf yaml-cpp boost numactl cpupower hwloc openmp clang htop && \
    pacman --noconfirm --force -Scc 

RUN cd ~ && \
    git clone https://github.com/realincubus/optci.git && \ 
    cd optci && \
    cmake . && \
    make -j 5

RUN cd ~ && \	
    git clone --depth=1 https://github.com/RRZE-HPC/likwid.git && \ 
    cd likwid && \
    make && make install     

# hpx installation think about different layer

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
    cmake -D CMAKE_CXX_STANDARD=14 -DCMAKE_INSTALL_PREFIX=/usr/ -DHPX_WITH_MALLOC=jemalloc .. 

RUN cd ~/hpx/build && \
    make -j 10

RUN cd ~/hpx/build && \
    make install

COPY run_tests.sh /run_tests.sh
