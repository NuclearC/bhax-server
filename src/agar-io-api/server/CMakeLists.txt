cmake_minimum_required(VERSION 3.6)
project(Cgar__)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(./websocketpp)

include_directories(./assets)

include_directories(./)

FIND_PACKAGE( Boost 1.40 COMPONENTS system)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(Cgar__ main.cpp)

TARGET_LINK_LIBRARIES( Cgar__ ${Boost_LIBRARIES} )