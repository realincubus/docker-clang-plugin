cmake_minimum_required(VERSION 2.6)

SET( CMAKE_EXPORT_COMPILE_COMMANDS true )

#find_package( optimizer_plugin )

# my flags 
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14" )

#TODO move this to optimizer_plugin-config.cmake as a macro
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -load -Xclang /root/libs/ClanPlugin.so -Xclang -add-plugin -Xclang clan -Xclang -plugin-arg-clan -Xclang -emit-openmp" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -plugin-arg-clan -Xclang -redirect-stdout -Xclang -plugin-arg-clan -Xclang /dev/null" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -plugin-arg-clan -Xclang -redirect-stderr -Xclang -plugin-arg-clan -Xclang /dev/null" )

add_executable( bin_main main.cpp )

