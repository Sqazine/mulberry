
find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
add_executable(Sprite Sprite.cpp)
target_include_directories(Sprite PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries( Sprite PRIVATE libPe2 SDL2::SDL2 SDL2::SDL2main spdlog::spdlog spdlog::spdlog_header_only glad::glad SDL2::SDL2_ttf)