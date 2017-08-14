############################################################
# Copyright (c) 2016 Stefan Kemnitz
# Released under the MIT license
############################################################

# ├─base/archlinux
#   ├─incubus/clang
#     ├─incubus/pet
#       ├─incubus/pluto
#         ├─incubus/plugin
#           ├─incubus/devel-turbovnc

FROM incubus/devel-turbovnc
MAINTAINER Stefan Kemnitz <kemnitz.stefan@googlemail.com>

# download the needed software 
RUN pacman -Syy --noconfirm && \
    pacman --noconfirm --force -S archlinux-keyring && \
    pacman --noconfirm --force -Su pacman && \
    pacman-db-upgrade && \
    pacman --noconfirm -S \
	qtcreator && \
    pacman --noconfirm --force -Scc

ADD qtexample /data/qtexample
ADD QtCreator.ini  /data/QtCreator.ini
ADD bashrc /data/bashrc
ADD config /data/config

ADD turboscript /turboscript_qtcreator
