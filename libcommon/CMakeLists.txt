cmake_minimum_required(VERSION 2.8.2)
project(libcommon)
enable_language(CXX)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/command_manager.h
   ${CMAKE_CURRENT_SOURCE_DIR}/commands.h
)

set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/internal/command_manager.cpp
)

add_library(libcommon ${HEADERS} ${SOURCE})

target_include_directories(libcommon
   PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}
   PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/internal
   )