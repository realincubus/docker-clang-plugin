############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang

FROM compus.physik.uni-greifswald.de:5000/kemnitzs/clang
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# Update and force a refresh of all package lists even if they appear up to date.
RUN pacman -Syy --noconfirm && \ 
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -Syu pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm --force -S cuda nvidia perl flex bison && \
    pacman --noconfirm --force -Scc 

RUN cd ~ && \
    git clone https://github.com/MentorEmbedded/nvptx-tools && \
    cd nvptx-tools && \
    ./configure --prefix=/usr/ && \
    make -j 20 && \
    make install && \
    cd .. && \
    rm -rf nvptx-tools

RUN cd ~ && \
    git clone --depth=1 https://github.com/MentorEmbedded/nvptx-newlib && \
    git clone --depth=1 https://github.com/gcc-mirror/gcc.git gcc && \
    cd gcc && \
    contrib/download_prerequisites && \
    ln -s ../nvptx-newlib/newlib newlib
    

RUN cd ~ && \
    target=$(gcc/config.guess) && \
    mkdir build-nvptx-gcc && \
    cd build-nvptx-gcc && \
    ../gcc/configure -C \
    --target=nvptx-none --with-build-time-tools=/usr/nvptx-none/bin \
    --enable-as-accelerator-for=$target \
    --disable-sjlj-exceptions \
    --enable-newlib-io-long-long \
    --enable-languages="c,c++,lto" \
    --prefix=/usr && \
    make -j 20 && \
    make install && \
    cd .. && \
    rm -rf build-nvptx-gcc


RUN cd ~ && \
    mkdir build-host-gcc && \
    cd build-host-gcc && \
    ../gcc/configure -C \
    --enable-offload-targets=nvptx-none \
    --disable-bootstrap \
    --disable-multilib \
    --enable-languages="c,c++,lto" \
    --prefix=/usr && \
    make -j 20 && \
    make install && \
    cd .. && \
    rm -rf build-host-gcc

# clean up for docker squash
RUN cd ~ && \
    rm -rf gcc nvptx-newlib || true && \
    pacman --noconfirm --force -R perl flex bison || true
