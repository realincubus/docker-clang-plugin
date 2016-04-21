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

COPY clang_3.9.patch /root/clang_3.9.patch

# install pet 
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm -S git bison flex autogen autoconf automake texinfo glibc libunistring && \
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
    make install && \
    cd $HOME/pet_install/ && \
    test -e include/isl/aff.h && \
    test -e lib/libisl.so.15 && \
    test -e lib/libpet_cxx.a
    
# install pluto 
RUN cd ~ && \
    git clone https://github.com/realincubus/pluto_clang.git pluto && \
    cd pluto && \
    git submodule update --init --recursive && \
    ./autogen.sh && \
    ./configure --enable-debug --prefix=$HOME/pluto_install && \
    make && \
    make install && \
    cd $HOME/pluto_install && \
    test -e lib/pluto/pluto-config.cmake && \
    test -e include/pluto/libpluto.h 
    

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

# TODO check whether ClanPlugin needs to be installed
COPY optimizer_plugin-config.cmake /root/build/lib/cmake/optimizer_plugin/optimizer_plugin-config.cmake

# build the tests 
RUN cd ~ && \
    git clone https://github.com/realincubus/clang_plugin_tests.git && \
    cd clang_plugin_tests && \
    export PATH=$HOME/pet_install/:$PATH && \
    export PATH=$HOME/pluto_install/:$PATH && \
    export PATH=$HOME/build/:$PATH && \
    cmake . && \
    test -e program_paths.sh

# to be able to run the container from this point
RUN cd ~ && \
    cd clang_plugin_tests && \
    ctest .






