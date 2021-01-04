cmake_minimum_required(VERSION 3.10)

project (CNN)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(CNN ${PROJECT_SOURCE_DIR}/src/array.cpp)
target_link_libraries(CNN ${OpenCV_LIBS})
