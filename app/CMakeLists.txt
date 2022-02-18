cmake_minimum_required(VERSION 3.21)
set(This App)
project(${This})

file(GLOB_RECURSE AppSources ${CMAKE_CURRENT_SOURCE_DIR}/src *.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_executable(${This} ${AppSources})
target_link_libraries(${This} LINK_PUBLIC Slime3D)
