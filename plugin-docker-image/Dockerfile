############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang
#     ├─incubus/pet
#       ├─incubus/pluto

FROM incubus/pluto
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# install needed software # TODO move packages to their containers
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm -S git bison flex autogen autoconf automake texinfo glibc libunistring intel-tbb && \
    pacman --noconfirm --force -Scc


RUN cd ~ && \
    git clone https://github.com/realincubus/ClanPlugin.git && \
    cd ClanPlugin
 
# build the plugin out of source using pet, pluto and clang
RUN export PATH=$PATH:$HOME/pet_install:$HOME/pluto_install:$HOME/install && \
    cd ~ && \
    cd ClanPlugin && \
    cmake -G "Ninja" . && \
    ninja

