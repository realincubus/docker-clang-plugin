############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─realincubus/clang
#     ├─realincubus/pet
#       ├─realincubus/pluto

FROM realincubus/pluto
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# download the plugin and change the cmakelists.txt
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm -S git bison flex autogen autoconf automake texinfo glibc libunistring && \
    pacman --noconfirm --force -Scc && \
    cd ~ && \
    cd llvm/tools/clang/examples/ && \
    git clone https://github.com/realincubus/ClanPlugin.git && \
    cd ClanPlugin && \
    git submodule update --init --recursive && \
    cd ~ && \
    cd llvm/tools/clang/examples/ && \
    echo "add_subdirectory(ClanPlugin)" >> CMakeLists.txt 
 
# rebuild the tree and provide info about all paths
RUN export pluto_codegen_cxx_DIR=$HOME/pet_install && \
    export pluto_DIR=$HOME/pluto_install && \
    export PATH=$PATH:$HOME/pet_install:$HOME/pluto_install && \
    cd ~ && \
    cd build/ && \
    ninja && \
    ninja lib/ClanPlugin.so

