############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux

FROM base/archlinux
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# Update and force a refresh of all package lists even if they appear up to date.
RUN pacman -Syy --noconfirm && \ 
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm --force -S db gcc vim subversion cmake make python grep sed ninja && \
    pacman --noconfirm --force -Scc 

    # get a clang install
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
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=release -DCMAKE_INSTALL_PREFIX=$HOME/install -G "Ninja" ../llvm && \
    ninja -j 1 && \
    ninja install 

# TODO patch the compiler with the right D15729 and the symbol list

COPY raw_diff /root/raw_diff

# TODO move the patch installation to the begin
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm -S patch && \
    pacman --noconfirm --force -Scc && \
    cd ~ && \
    cd llvm/tools/clang && \
    ls -la && \
    patch -p0 < /root/raw_diff && \
    cd ~ && \
    cd build && \
    ninja -j 1 && \
    ninja install 


