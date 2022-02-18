cmake_minimum_required(VERSION 3.21)
set(This Slime3D)
project(${This})

# find packages for dependencies
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)

# glfw doesn't set it's libraries variable properly
set(GLFW_LIBRARIES glfw)

# find all our source files
file(GLOB_RECURSE EngineSources ${CMAKE_CURRENT_SOURCE_DIR}/src *.cpp)

# include all headers from our src directory
set(EngineHeadersDir ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${EngineHeadersDir})

# create a library from our source files
add_library(${This} STATIC ${EngineSources})
# include our headers dir with the target
target_include_directories(${This} PUBLIC ${EngineHeadersDir})
# link our dependencies to the target
target_link_libraries(${This} PUBLIC ${GLFW_LIBRARIES} ${Vulkan_LIBRARIES} ${GLEW_LIBRARIES})
