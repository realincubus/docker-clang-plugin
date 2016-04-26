############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─realincubus/clang

FROM realincubus/clang
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

COPY clang_3.9.patch /root/clang_3.9.patch

# install pet 
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm -S git bison flex autogen autoconf automake texinfo glibc libunistring libyaml && \
    pacman --noconfirm --force -Scc && \
    cd ~ && \
    mkdir pet_install && \
    git clone https://github.com/realincubus/pet.git && \
    cd pet && \
     git submodule update --init --recursive && \
    cd isl && \
    patch -p1 < /root/clang_3.9.patch && \
    cd .. && \
    ./autogen.sh && \
    ./configure --with-clang-prefix=$HOME/install --prefix=$HOME/pet_install --with-pic  && \
    make && \
    make pet &&\
    make pet_scop_cmp && \
    make install && \
    cd $HOME/pet_install/ && \
    test -e include/isl/aff.h && \
    test -e lib/libisl.so.15 && \
    test -e lib/libpet_cxx.a
    

