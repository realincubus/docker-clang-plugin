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


FROM incubus/devel
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# Update and force a refresh of all package lists even if they appear up to date.
RUN pacman -Syy --noconfirm && \ 
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -Syu pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm --force -S bc perf yaml-cpp boost numactl && \
    pacman --noconfirm --force -Scc 

#RUN cd ~ \
#    git clone https://github.com/jbeder/yaml-cpp.git && \
#    cd yaml-cpp && \
#    cmake -DBUILD_SHARED_LIBS=on -DCMAKE_BUILD_TYPE=release . && \
#    make -j 5 && \
#    make install  

RUN cd ~ && \
    git clone https://github.com/realincubus/optci.git && \ 
    cd optci && \
    cmake . && \
    make -j 5