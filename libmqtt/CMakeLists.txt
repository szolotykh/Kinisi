cmake_minimum_required(VERSION 2.8.2)
project(libmqtt)
enable_language(CXX)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/mqttclient.h
   ${CMAKE_CURRENT_SOURCE_DIR}/mqttworker.h
   ${CMAKE_CURRENT_SOURCE_DIR}/mqttcommands.h
)

set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/mqttclient.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/mqttworker.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/mqttcommands.cpp
)

find_package (Threads)

add_library(libmqtt ${HEADERS} ${SOURCE})
target_link_libraries(libmqtt ${CMAKE_THREAD_LIBS_INIT} libpaho-mqttpp3.so)