cmake_minimum_required(VERSION 3.13.4)

set(This engine)
project(${This} C CXX)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

IF (WIN32)
    set(FMOD_PATH ${PROJECT_SOURCE_DIR}/vendor/fmod/windows/api/core)

    add_library(fmod STATIC IMPORTED)

    find_package(glm REQUIRED)
    get_target_property(GLM_INCLUDE_DIR glm INTERFACE_INCLUDE_DIRECTORIES)
    get_target_property(GLFW_LIBRARIES glfw IMPORTED_IMPLIB_RELEASE)

    set(_ENGINE_INCLUDE_DIRS ${FMOD_PATH}/inc)
    set(_ENGINE_LIBRARIES ${FMOD_PATH}/lib/x64/fmod_vc.lib ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${Vulkan_LIBRARIES})
ELSE ()
    set(FMOD_PATH ${PROJECT_SOURCE_DIR}/vendor/fmod/linux/api/core)

    add_library(fmod SHARED IMPORTED)

    get_target_property(GLFW_LIBRARIES glfw IMPORTED_LOCATION_NOCONFIG)
    set(_ENGINE_INCLUDE_DIRS ${FMOD_PATH}/inc)
    set(_ENGINE_LIBRARIES /usr/lib/fmod/libfmod.so ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${Vulkan_LIBRARIES})
ENDIF ()

get_target_property(GLFW_INCLUDE_DIR glfw INTERFACE_INCLUDE_DIRECTORIES)
list(APPEND _ENGINE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src ${Vulkan_INCLUDE_DIRS} ${GLM_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR})
set(ENGINE_INCLUDE_DIRS ${_ENGINE_INCLUDE_DIRS} PARENT_SCOPE)
set(ENGINE_LIBRARIES ${_ENGINE_LIBRARIES} PARENT_SCOPE)

file(GLOB VendorHeaders ${PROJECT_SOURCE_DIR}/vendor/**/*.h)
file(GLOB EngineHeaders ${PROJECT_SOURCE_DIR}/src/**/*.hpp)

set(Headers ${VendorHeaders} ${EngineHeaders})

include_directories(${_ENGINE_INCLUDE_DIRS})
add_library(${This} STATIC ${PROJECT_SOURCE_DIR}/src/main.cpp ${Headers})
target_include_directories(${This} INTERFACE ${_ENGINE_INCLUDE_DIRS})

IF (WIN32)
    target_link_libraries(${This} PUBLIC ${_ENGINE_LIBRARIES} glm)
ELSE ()
    target_link_libraries(${This} PUBLIC ${_ENGINE_LIBRARIES})
ENDIF ()
