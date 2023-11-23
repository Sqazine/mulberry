project(SDL_ttf C)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/freetype-2.9.1")

set(SDL_TTF_MAJOR_VERSION 2)
set(SDL_TTF_MINOR_VERSION 0)
set(SDL_TTF_MICRO_VERSION 8)
set(SDL_TTF_INTERFACE_AGE 0)
set(SDL_TTF_BINARY_AGE 14)
set(SDL_TTF_VERSION "${SDL_TTF_MAJOR_VERSION}.${SDL_TTF_MINOR_VERSION}.${SDL_TTF_MICRO_VERSION}")

add_library(SDL2_ttf SDL_ttf.c SDL_ttf.h)
target_link_libraries(SDL2_ttf SDL2 Freetype)
target_include_directories(SDL2_ttf PUBLIC ${SDL_INC_DIR})