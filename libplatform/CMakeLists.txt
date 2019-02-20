cmake_minimum_required(VERSION 2.8.2)
project(libplatform)
enable_language(CXX)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/platform.h
   ${CMAKE_CURRENT_SOURCE_DIR}/hwplatform.h
   ${CMAKE_CURRENT_SOURCE_DIR}/virtualplatform.h
   ${CMAKE_CURRENT_SOURCE_DIR}/platformcommands.h
   ${CMAKE_CURRENT_SOURCE_DIR}/platformworker.h
   ${CMAKE_CURRENT_SOURCE_DIR}/devices/motor.h
   ${CMAKE_CURRENT_SOURCE_DIR}/devices/current_sensor.h
)

set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/platform.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/hwplatform.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/virtualplatform.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/platformcommands.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/platformworker.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/devices/motor.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/devices/current_sensor.cpp
)



add_library(libplatform ${HEADERS} ${SOURCE})

target_include_directories(libplatform
   PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}/devices
   )

target_link_libraries(libplatform ${CMAKE_THREAD_LIBS_INIT} libcommon phidget22.so)