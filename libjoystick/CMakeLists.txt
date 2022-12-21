cmake_minimum_required(VERSION 2.8.2)

# libmqtt project
project(libjoystick)
enable_language(CXX)

# Header files
set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/joystick.h
   ${CMAKE_CURRENT_SOURCE_DIR}/joystickworker.h
   "joystickevents.h"
)

# Source files
set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/internal/joystickworker.cpp
   "internal/joystickevents.cpp"
)


# Target
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCE})

target_include_directories(${PROJECT_NAME}
   PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}
   PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/internal
   )