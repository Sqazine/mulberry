cmake_minimum_required(VERSION 3.10)

project(mulberry)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS  OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Binary/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Binary/Release)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "current platform: Linux")
    set(CURRENT_PLATFORM PLATFORM_LINUX)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "current platform: Windows")
    set(CURRENT_PLATFORM PLATFORM_WINDOWS)
elseif (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    message(STATUS "current platform: FreeBSD")
    set(CURRENT_PLATFORM PLATFORM_FREEBSD)
else ()
    message(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
    set(CURRENT_PLATFORM PLATFORM_OTHER)
endif ()

message(STATUS "CURRENT_PLATFORM=${CURRENT_PLATFORM}")

set(SDL_INC_DIR "${CMAKE_SOURCE_DIR}/3rd/SDL/include")
set(SDL_TTF_INC_DIR "${CMAKE_SOURCE_DIR}/3rd/SDL_ttf")

set(THIRD_PARTY_DIR "${CMAKE_SOURCE_DIR}/3rd")

add_subdirectory("${CMAKE_SOURCE_DIR}/3rd/SDL")
add_subdirectory("${CMAKE_SOURCE_DIR}/3rd/SDL_ttf")
add_subdirectory("${CMAKE_SOURCE_DIR}/3rd/glad")
add_subdirectory("${CMAKE_SOURCE_DIR}/3rd/glslang")
add_subdirectory("${CMAKE_SOURCE_DIR}/3rd/spdlog")
add_subdirectory("${CMAKE_SOURCE_DIR}/3rd/stb")

add_subdirectory(${CMAKE_SOURCE_DIR}/mulberry)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests/Sprite)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests/Asteroid)