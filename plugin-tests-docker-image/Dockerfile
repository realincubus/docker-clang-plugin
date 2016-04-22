############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─realincubus/clang
#     ├─realincubus/pet
#       ├─realincubus/pluto
#         |-realincubus/plugin

FROM realincubus/plugin
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

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

COPY keep_running.sh /keep_running.sh
COPY run.sh /run.sh

ENTRYPOINT /keep_running.sh



