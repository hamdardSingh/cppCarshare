cmake_minimum_required (VERSION 3.3.2)
project (client)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.57.0 REQUIRED system serialization)

set(CLIENT_SRC ./client.cpp)
set(CLIENT_HEADERS includes/client.h includes/network.h)

set(SERVER_SRC ./server/server.cpp)
set(SERVER_HEADERS ./server/includes/handel.h)

if(Boost_FOUND)
  message(STATUS "Boost Found!")
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories("${Boost_LIBRARY_DIRS}")

  add_executable(client ${CLIENT_SRC} ${CLIENT_HEADERS} )
  add_executable(server ${SERVER_SRC} ${SERVER_HEADERS} )
  target_link_libraries(client boost_system boost_serialization)
  target_link_libraries(server boost_system boost_serialization)
else()
  message(STATUS "Boost NOT Found!")
endif()
