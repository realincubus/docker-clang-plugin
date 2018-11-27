############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang
#     ├─incubus/pet
#       ├─incubus/pluto

FROM compus.physik.uni-greifswald.de:5000/kemnitzs/pluto
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

#TODO implement something to install the plugin and then remove the compilation folder
ARG OSIZE=1
ARG JOBS=2

# install needed software # TODO move packages to their containers
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm -S git bison flex autogen autoconf automake texinfo glibc libunistring intel-tbb && \
    pacman --noconfirm --force -Scc


RUN cd ~ && \
    git clone --depth=1 https://github.com/realincubus/ClanPlugin.git && \
    cd ClanPlugin && \
    git submodule update --init
 
# build the plugin out of source using pet, pluto and clang
RUN export PATH=$PATH:$HOME/pet_install:$HOME/pluto_install:$HOME/install && \
    export CPATH=$CPATH:$HOME/pet_install/include:$HOME/pluto_install/include/pluto/:$HOME/pluto_install/include/pluto_codegen_cxx:$HOME/install/include/ && \
    cd ~ && \
    cd ClanPlugin && \
    cmake -G "Ninja" . && \
    ninja -j $JOBS

