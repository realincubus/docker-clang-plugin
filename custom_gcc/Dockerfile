############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang

FROM incubus/clang
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# Update and force a refresh of all package lists even if they appear up to date.
RUN pacman -Syy --noconfirm && \ 
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -Syu pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm --force -S cuda svn nvidia && \
    pacman --noconfirm --force -Scc 

RUN cd ~ && \
    git clone https://github.com/MentorEmbedded/nvptx-tools && \
    cd nvptx-tools && \
    ./configure --prefix=/usr/ && \
    make -j 20 && \
    make install

RUN cd ~ && \
    git clone --depth=1 https://github.com/MentorEmbedded/nvptx-newlib && \
    git clone --depth=1 https://github.com/gcc-mirror/gcc.git gcc && \
    cd gcc && \
    contrib/download_prerequisites && \
    ln -s ../nvptx-newlib/newlib newlib
    
RUN pacman --noconfirm --force -S perl
RUN pacman --noconfirm --force -S flex bison

RUN cd ~ && \
    target=$(gcc/config.guess) && \
    mkdir build-nvptx-gcc && \
    cd build-nvptx-gcc && \
    ../gcc/configure \
    --target=nvptx-none --with-build-time-tools=/usr/nvptx-none/bin \
    --enable-as-accelerator-for=$target \
    --disable-sjlj-exceptions \
    --enable-newlib-io-long-long \
    --enable-languages="c,c++,lto" \
    --prefix=/usr 

RUN cd ~ && \
    cd build-nvptx-gcc && \
    make -j 20 && \
    make install 


RUN cd ~ && \
    mkdir build-host-gcc && \
    cd build-host-gcc && \
    ../gcc/configure \
    --enable-offload-targets=nvptx-none \
    --disable-bootstrap \
    --disable-multilib \
    --enable-languages="c,c++,lto" \
    --prefix=/usr && \
    make -j 20 && \ 
    make install

