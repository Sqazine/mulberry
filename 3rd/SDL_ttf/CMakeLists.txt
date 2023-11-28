project(SDL_ttf C)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(SDL_TTF_MAJOR_VERSION 2)
set(SDL_TTF_MINOR_VERSION 0)
set(SDL_TTF_MICRO_VERSION 8)
set(SDL_TTF_INTERFACE_AGE 0)
set(SDL_TTF_BINARY_AGE 14)
set(SDL_TTF_VERSION "${SDL_TTF_MAJOR_VERSION}.${SDL_TTF_MINOR_VERSION}.${SDL_TTF_MICRO_VERSION}")

add_library(SDL2_ttf SDL_ttf.c SDL_ttf.h)
target_link_libraries(SDL2_ttf SDL2-static freetype)
target_include_directories(SDL2_ttf PUBLIC ${SDL_INC_DIR} ${FREETYPE_INC_DIR})