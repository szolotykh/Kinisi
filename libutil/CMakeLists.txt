cmake_minimum_required(VERSION 2.8.2)
project(libutil)
enable_language(CXX)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/util.h
)

set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/util.cpp
)

add_library(libutil ${HEADERS} ${SOURCE})