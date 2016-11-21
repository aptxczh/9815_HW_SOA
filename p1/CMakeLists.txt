cmake_minimum_required(VERSION 2.8)
project(cppcodetest)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -DEIGEN_NO_DEBUG -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lrt")
set(CMAKE_BUILD_TYPE, "Debug")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include_directories("/usr/include/boost")

set(SOURCE_FILES
        test_interprocess.cpp)

add_executable(cppcodetest ${SOURCE_FILES})
