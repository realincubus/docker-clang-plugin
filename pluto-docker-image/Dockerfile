############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─realincubus/clang
#     ├─realincubus/pet

FROM realincubus/pet
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>
   
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
   
COPY run.sh /run.sh

ENTRYPOINT /run.sh 
