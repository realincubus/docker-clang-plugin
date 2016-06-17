#!/bin/bash -x

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
cd ClanPlugin
git pull
export PATH=$PATH:$HOME/pet_install
export PATH=$PATH:$HOME/pluto_install
export PATH=$PATH:$HOME/install
ninja 

# run plugin tests
cd ~ 
cd clang_plugin_tests 
export PATH=$HOME/pet_install/:$PATH && \
export PATH=$HOME/pluto_install/:$PATH && \
export PATH=$HOME/install/:$PATH && \
export PATH=$HOME/ClanPlugin/:$PATH && \
git pull 
cmake .
ctest --no-compress-output -T Test . 

# run pluto tests
cd ~ 
cd pluto/test 
git pull || true
make
cmake .
ctest --no-compress-output -T Test . 

# run pet tests
cd ~
cd pet
mkdir pet_cmake_testing
cd pet_cmake_testing
git pull 
make
cmake ..
ctest --no-compress-output -T Test . 

#echo remove old test results 
rm -r /host/*

echo "host folder content"
ls /host
rm -rf /host/pet_results
rm -rf /host/pluto_results
rm -rf /host/plugin_results
echo "done host folder content"

echo "copy plugin results to the host"
cd ~ 
cp -r clang_plugin_tests/Testing /host/plugin_results

# copy pluto test results to the host
cp -r pluto/test/Testing /host/pluto_results/

# copy pet test results to the host
cp -r pet/pet_cmake_testing/Testing /host/pet_results/

chmod 777 -R /host/pet_results
chmod 777 -R /host/pluto_results
chmod 777 -R /host/plugin_results






