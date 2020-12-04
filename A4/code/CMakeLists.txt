cmake_minimum_required(VERSION 3.10)

project (matrix)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(./src DIR_SRCS)

include_directories(include)

add_executable (test ${DIR_SRCS})
