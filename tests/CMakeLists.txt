cmake_minimum_required(VERSION 2.6)
 
include_directories(../lib ../vendor/include ../vendor/src/gtest)

set(GTEST_SOURCES ../vendor/src/gtest/src/*.cc)

add_subdirectory(peacemaker-test)