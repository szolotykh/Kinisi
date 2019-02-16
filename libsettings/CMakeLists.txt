cmake_minimum_required(VERSION 2.8.2)
project(libsettings)
enable_language(CXX)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/libsettings.h
)

set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/libsettings.cpp
)

add_library(libsettings ${HEADERS} ${SOURCE})
target_link_libraries(libsettings ${CMAKE_THREAD_LIBS_INIT} json11)