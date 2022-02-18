cmake_minimum_required(VERSION 3.21)
project(Slime3DWrapper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_subdirectory (engine)
add_subdirectory (app)
