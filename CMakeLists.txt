cmake_minimum_required(VERSION 3.0)
project(TidaLink)
include(${CMAKE_SOURCE_DIR}/link/AbletonLinkConfig.cmake)
set(SOURCES
  ${SOURCES}
  ${CMAKE_SOURCE_DIR}/main.cpp
  )
add_executable(TidaLink ${SOURCES} ${INCLUDES})
target_link_libraries(TidaLink Ableton::Link)
