cmake_minimum_required(VERSION 3.10)


set(VCPKG_ROOT "$ENV{VCPKG_ROOT}" CACHE STRING "")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE STRING "")

message("CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")
message("VCPKG_TARGET_TRIPLET=${VCPKG_TARGET_TRIPLET}")

project(mulberry LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_SOURCE_DIR}/libmulberry)
add_subdirectory(${CMAKE_SOURCE_DIR}/Tests/Sprite)
add_subdirectory(${CMAKE_SOURCE_DIR}/Tests/Asteroid)