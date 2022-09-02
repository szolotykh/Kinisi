cmake_minimum_required (VERSION 2.8.2)
 

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
include_directories("${PROJECT_SOURCE_DIR}/libutil")
include_directories("${PROJECT_SOURCE_DIR}/libcommon")
include_directories("${PROJECT_SOURCE_DIR}/libjoystick")

# Add subdirectories
add_subdirectory("${PROJECT_SOURCE_DIR}/libsettings")
add_subdirectory("${PROJECT_SOURCE_DIR}/libmqtt")
add_subdirectory("${PROJECT_SOURCE_DIR}/libplatform")
add_subdirectory("${PROJECT_SOURCE_DIR}/libutil")
add_subdirectory("${PROJECT_SOURCE_DIR}/libcommon")
add_subdirectory("${PROJECT_SOURCE_DIR}/libjoystick")


# Executables
add_executable(robot ${SOURCE} ${HEADERS} robot.cpp)
target_link_libraries(robot ${CMAKE_THREAD_LIBS_INIT} libutil libmqtt libsettings libplatform libjoystick)
