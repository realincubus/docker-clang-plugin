############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang
#     ├─incubus/pet
#       ├─incubus/pluto
#         |-incubus/plugin

FROM compus.physik.uni-greifswald.de:5000/kemnitzs/plugin
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# install needed software # TODO move packages to their containers
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm -S gtest && \
    pacman --noconfirm --force -Scc

# build the tests 
RUN cd ~ && \
    git clone https://github.com/realincubus/clang_plugin_tests.git && \
    cd clang_plugin_tests && \
    export PATH=$HOME/pet_install/:$PATH && \
    export PATH=$HOME/pluto_install/:$PATH && \
    export PATH=$HOME/install/:$PATH && \
    export PATH=$HOME/ClanPlugin/:$PATH && \
    cmake . && \
    test -e program_paths.sh

COPY keep_running.sh /keep_running.sh
COPY run.sh /run.sh

ENTRYPOINT /keep_running.sh



