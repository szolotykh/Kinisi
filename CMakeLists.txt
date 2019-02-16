cmake_minimum_required (VERSION 2.8.2)
project (robot)

set(CMAKE_CXX_STANDARD 17)

# The version number.
set (ROBOT_VERSION_MAJOR 0)
set (ROBOT_VERSION_MINOR 1)

set(CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build") #bin
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/libsettings")
include_directories("${PROJECT_SOURCE_DIR}/libplatform")
include_directories("${PROJECT_SOURCE_DIR}/libmqtt")


set(HEADERS
   ${CMAKE_CURRENT_SOURCE_DIR}/settings.h
   ${HEADERS}
)

set(SOURCE
   ${CMAKE_CURRENT_SOURCE_DIR}/settings.cpp
   ${SOURCE}
)

# Add subdirectories
add_subdirectory("${PROJECT_SOURCE_DIR}/libsettings")
add_subdirectory("${PROJECT_SOURCE_DIR}/libmqtt")
add_subdirectory("${PROJECT_SOURCE_DIR}/libplatform")


# Executables
add_executable(robot ${SOURCE} ${HEADERS} robot.cpp)
target_link_libraries(robot ${CMAKE_THREAD_LIBS_INIT} libmqtt libsettings)

add_executable(ptest platformtest.cpp)
target_link_libraries(ptest ${CMAKE_THREAD_LIBS_INIT} libplatform)