#!/bin/bash -xe

#./build

#cd pet-docker-image
#./build
#cd ..

cd pluto-docker-image
./build
cd ..

cd plugin-docker-image
./build
cd ..

cd plugin-tests-docker-image
./build
cd ..

cd ycm-docker-image
./build
cd ..
