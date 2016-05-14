############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux

FROM base/archlinux
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

ARG JOBS=1

# Update and force a refresh of all package lists even if they appear up to date.
RUN pacman -Syy --noconfirm && \ 
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm --force -Syu pacman && \
    pacman --noconfirm --force -S db gcc vim subversion cmake make python grep sed ninja patch && \
    pacman --noconfirm --force -Scc 

COPY raw_diff /root/raw_diff
COPY export_symbols /root/export_symbols

# get a clang install patch it, install it and remove all unnecessary stuff
RUN cd ~ && \
    svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm && \
    cd llvm/tools && \
    svn co http://llvm.org/svn/llvm-project/cfe/trunk clang && \
    cd ../.. && \
    cd llvm/tools/clang/tools && \
    svn co http://llvm.org/svn/llvm-project/clang-tools-extra/trunk extra && \
    cd ../../../.. && \
    mkdir install && \
    mkdir build && \
    cd ~ && \
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
    rm -r build && \
    rm -r llvm  

# TODO move the patch installation to the begin
#RUN pacman -Syy --noconfirm && \
#    pacman --noconfirm --force -S archlinux-keyring && \
#    pacman --noconfirm --force -S pacman && \
#    pacman-db-upgrade && \
#    pacman --noconfirm -S patch && \
#    pacman --noconfirm --force -Scc && \
#    cd ~ && \
#    cd llvm/tools/clang && \
#    patch -p0 < /root/raw_diff && \
#    cd ~ && \
#    cd build && \
#    ninja -j 1 && \
#    ninja install 
