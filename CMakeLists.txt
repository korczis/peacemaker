cmake_minimum_required(VERSION 2.6)
 
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(apps) 
add_subdirectory(lib)