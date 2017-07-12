############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang
#     ├─incubus/gcc

FROM incubus/gcc
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

ARG OSIZE=1
ARG JOBS=2


# install pet 
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman --noconfirm --force -Syu && \
    pacman-db-upgrade && \
    pacman --noconfirm -S git bison flex autogen autoconf automake texinfo glibc libunistring libyaml && \
    pacman --noconfirm --force -Scc

COPY clang_5.0_libs.patch /root/clang.patch

RUN cd ~ && \
    mkdir pet_install && \
     git clone --depth=1 https://github.com/realincubus/pet.git && \
    cd pet && \
    git submodule update --init --recursive && \
    cd isl && \
    git apply /root/clang.patch && \
    cd .. && \
    ./autogen.sh && \
    ./configure --with-clang-prefix=$HOME/install --prefix=$HOME/pet_install --with-pic  && \
    make -j $JOBS && \
    make pet &&\
    make pet_scop_cmp && \
    make install && \
    cd $HOME/pet_install/ && \
    test -e include/isl/aff.h && \
    test -e lib/libisl.so.15 && \
    test -e lib/libpet_cxx.a && \
    if `test $OSIZE -eq 1` ; then rm -rf $HOME/pet; else echo "did not remove the pet folder"; fi
    

