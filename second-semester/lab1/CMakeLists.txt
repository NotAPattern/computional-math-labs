cmake_minimum_required(VERSION 3.10)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/matrix-master/dist/includes)
set(PROJECT_SRC_DIR ${PROJECT_SOURCE_DIR}/matrix-master/dist/src)

include_directories(${PROJECT_HEADERS_DIR})

file(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*.h)
file(GLOB_RECURSE SOURCES ${PROJECT_SRC_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} main.cpp)


# add_executable(vk_terminal main.cpp)

# add_executable(lab1 main.cpp)