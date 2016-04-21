#!/bin/bash

# update pet
cd ~
cd pet
git pull
git submodule update
make 
make install

#update pluto
cd ~
cd pluto
git pull 
git submodule update
make 
make install

#update plugin
cd ~ 
cd llvm/tools/clang/examples/ClanPlugin
git pull
cd ~ 
cd build 
export pluto_codegen_cxx_DIR=$HOME/pet_install
export pluto_DIR=$HOME/pluto_install
export PATH=$PATH:$HOME/pet_install:$HOME/pluto_install
ninja lib/ClanPlugin.so

# run the tests
cd ~ 
cd clang_plugin_tests 
export PATH=$HOME/pet_install/:$PATH && \
export PATH=$HOME/pluto_install/:$PATH && \
export PATH=$HOME/build/:$PATH && \
git pull 
cmake .
ctest . 
cd ~ 
cd pluto 
make test 
