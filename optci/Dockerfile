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


FROM compus.physik.uni-greifswald.de:5000/kemnitzs/devel-pic2d
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# Update and force a refresh of all package lists even if they appear up to date.
RUN pacman -Syy --noconfirm && \ 
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -Syu pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm --force -S bc perf yaml-cpp boost numactl cpupower hwloc openmp clang htop sysstat && \
    pacman --noconfirm --force -Scc 

RUN cd ~ && \
    git clone https://github.com/realincubus/optci.git && \ 
    cd optci && \
    cmake . && \
    make

RUN cd ~ && \	
    git clone --depth=1 https://github.com/RRZE-HPC/likwid.git && \ 
    cd likwid && \
    make && make install     

COPY run_tests.sh /run_tests.sh
