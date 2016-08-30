############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang
#     ├─incubus/pet

FROM incubus/pet
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

ARG OSIZE=1
ARG JOBS=1
   
# install pluto 
RUN cd ~ && \
    git clone --depth=1 https://github.com/realincubus/pluto_clang.git pluto && \
    cd pluto && \
    git submodule update --init --recursive && \
    ./autogen.sh && \
    ./configure --with-pic --enable-debug --prefix=$HOME/pluto_install && \
    make -j $JOBS && \
    make install && \
    cd $HOME/pluto_install && \
    test -e lib/pluto/pluto-config.cmake && \
    test -e include/pluto/libpluto.h && \
    if `test $OSIZE -eq 1` ; then rm -rf $HOME/pluto ; fi
   
