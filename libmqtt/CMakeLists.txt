cmake_minimum_required(VERSION 2.8.2)

# libmqtt project
project(libmqtt)
enable_language(CXX)

# Header files
set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/mqttclient.h
   ${CMAKE_CURRENT_SOURCE_DIR}/mqttworker.h
   ${CMAKE_CURRENT_SOURCE_DIR}/mqttcommands.h
)

# Source files
set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/internal/mqttclient.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/internal/mqttworker.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/internal/mqttcommands.cpp
)

# Find all required packages
find_package (Threads) # We need it for paho

# Target
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCE})

target_include_directories(${PROJECT_NAME}
   PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}
   PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/internal
   )

target_link_libraries(${PROJECT_NAME} libcommon ${CMAKE_THREAD_LIBS_INIT} libpaho-mqttpp3.so libpaho-mqtt3as.so)