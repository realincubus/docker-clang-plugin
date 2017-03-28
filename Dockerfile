############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux

FROM base/archlinux
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

ARG JOBS=1
ARG OSIZE=1

# Update and force a refresh of all package lists even if they appear up to date.
RUN pacman -Syy --noconfirm && \ 
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm --force -Syu pacman && \
    pacman --noconfirm --force -S db gcc vim git cmake make python2 grep sed ninja patch && \
    pacman --noconfirm --force -Scc 

# get a clang install patch it, install it and remove all unnecessary stuff
RUN cd ~ && \
    git clone --depth=1 https://github.com/llvm-mirror/llvm.git && \
    cd llvm/tools && \
    git clone --depth=1 https://github.com/llvm-mirror/clang.git && \
    cd ~ && \
    mkdir install && \
    mkdir build 

COPY raw_diff /root/raw_diff
COPY export_symbols /root/export_symbols

RUN cd ~ && \
    cd llvm/tools/clang && \
    patch -p0 < /root/raw_diff && \
    cd ~ &&\
    cd llvm/tools/clang/tools/libclang && \
    cat /root/export_symbols >> libclang.exports && \
    cd ~ && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=release -DCMAKE_INSTALL_PREFIX=$HOME/install -G "Ninja" ../llvm && \
    ninja -j $JOBS && \
    ninja install && \
    cd ~ && \
    if `test $OSIZE -eq 1 `; then rm -r build ; fi && \
    if `test $OSIZE -eq 1 `; then rm -r llvm ; fi 

