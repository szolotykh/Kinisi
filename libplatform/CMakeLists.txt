cmake_minimum_required(VERSION 2.8.2)
project(libplatform)
enable_language(CXX)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/platform.h
   ${CMAKE_CURRENT_SOURCE_DIR}/virtualplatform.h
   ${CMAKE_CURRENT_SOURCE_DIR}/platformcommands.h
   ${CMAKE_CURRENT_SOURCE_DIR}/platformworker.h
)

set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/platform.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/virtualplatform.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/platformcommands.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/platformworker.cpp
)



add_library(libplatform ${HEADERS} ${SOURCE} "kinisi_platform/controller.h" "kinisi_platform/kinisiplatform.cpp" "kinisi_platform/kinisiplatform.h" "kinisi_platform/controller.cpp" "kinisi_platform/kinisicommands.h")

target_include_directories(libplatform
   PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}/devices
   )

target_link_libraries(libplatform ${CMAKE_THREAD_LIBS_INIT} libcommon)