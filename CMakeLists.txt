project(Tetris)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(./src SRC_LIST)
include_directories(./src)

set(SRC_LIST ${SRC_LIST} ./src/Utility.hpp ./src/Utility.inl ./src/ResourceHolder.hpp ./src/ResourceHolder.inl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_definitions(-DDEBUG)

find_package(SFML 2 REQUIRED system window graphics network audio)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
