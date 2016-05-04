cmake_minimum_required(VERSION 2.6)

SET( CMAKE_EXPORT_COMPILE_COMMANDS true )

find_package( optimizer_plugin )

#TODO move this to optimizer_plugin-config.cmake as a macro
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -load -Xclang ${OPTIMIZER_PLUGIN_LIBRARY} -Xclang -add-plugin -Xclang clan" )

add_executable( bin_main main.cpp )

