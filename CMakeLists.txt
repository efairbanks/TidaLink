cmake_minimum_required(VERSION 3.0)
project(TidaLink)
#include_directories(include)
include(${CMAKE_SOURCE_DIR}/link/AbletonLinkConfig.cmake)
#file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/link/examples/linkaudio/AudioPlatform.cpp")
#file(GLOB INCLUDES "${CMAKE_SOURCE_DIR}/link/examples/linkaudio/AudioPlatform.hpp")
#set(INCLUDES
#  ${INCLUDES}
#  "${CMAKE_SOURCE_DIR}/link/examples/linkaudio/AudioPlatform.hpp")
set(SOURCES
  ${SOURCES}
  ${CMAKE_SOURCE_DIR}/main.cpp
  )
#set(INCLUDES
#  ${INCLUDES}
#  ${link_HEADERS}
#  )
add_executable(TidaLink ${SOURCES} ${INCLUDES})
target_link_libraries(TidaLink Ableton::Link)
#target_link_libraries(TidaLink "-framework AudioUnit")
#target_compile_definitions(TidaLink PRIVATE
#  -DLINKHUT_AUDIO_PLATFORM_COREAUDI1
#  )
