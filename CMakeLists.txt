cmake_minimum_required(VERSION 3.0)
project(TidaLink)
include(${CMAKE_SOURCE_DIR}/link/AbletonLinkConfig.cmake)
#add_subdirectory(${CMAKE_SOURCE_DIR}/oscpack)
set(INCLUDES
  ${INCLUDES}
  ${CMAKE_SOURCE_DIR}/dirtyudp.h
  ${CMAKE_SOURCE_DIR}/oscpack/osc/OscOutboundPacketStream.h
  ${CMAKE_SOURCE_DIR}/oscpack/osc/OscReceivedElements.h
  ${CMAKE_SOURCE_DIR}/oscpack/osc/OscPacketListener.h
  #${CMAKE_SOURCE_DIR}/oscpack/ip/UdpSocket.h
  )
set(SOURCES
  ${SOURCES}
  ${CMAKE_SOURCE_DIR}/main.cpp
  ${CMAKE_SOURCE_DIR}/oscpack/osc/OscOutboundPacketStream.cpp
  ${CMAKE_SOURCE_DIR}/oscpack/osc/OscReceivedElements.cpp
  #${CMAKE_SOURCE_DIR}/oscpack/ip/UdpSocket.cpp
  )
add_executable(TidaLink ${SOURCES} ${INCLUDES})
find_package (Threads) 
target_link_libraries(TidaLink Ableton::Link ${CMAKE_THREAD_LIBS_INIT})
#target_link_libraries(TidaLink oscpack)
