#!/bin/bash

#TODO do not update if there was no change

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

# run plugin tests
cd ~ 
cd clang_plugin_tests 
export PATH=$HOME/pet_install/:$PATH && \
export PATH=$HOME/pluto_install/:$PATH && \
export PATH=$HOME/build/:$PATH && \
git pull 
cmake .
ctest --no-compress-output -T Test . 

# run pluto tests
#cd ~ 
#cd pluto 
#make test 

# TODO run pet tests

#echo remove old test results 
#rm -r /host/*

echo "host folder content"
ls /host
echo "done host folder content"

echo "copy plugin results to the host"
cd ~ 
cp -r clang_plugin_tests/Testing /host/

# TODO copy pluto test results to the host

# TODO copy pet test results to the host
