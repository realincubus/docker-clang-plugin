############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang
#     ├─incubus/pet
#       ├─incubus/pluto
#         ├─incubus/plugin
#           ├─incubus/ycm

FROM incubus/plugin-tests
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# download the needed software 
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -S pacman && \
    pacman-db-upgrade && \
    #pacman --noconfirm --force -Syu && \
    pacman --noconfirm -S zsh && \
    pacman --noconfirm --force -Scc
 

COPY bashrc /root/.bashrc
COPY bashrc /root/.zshrc
