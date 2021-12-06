file(GLOB ROOT "*.h" "*.cpp")
file(GLOB MATH "Math/*.h" "Math/*.cpp")
file(GLOB GEOMETRY "Math/Geometry/*.h" "Math/Geometry/*.cpp")
file(GLOB SCENE "Scene/*.h" "Scene/*.cpp")
file(GLOB COMPONENT "Scene/Component/*.h" "Scene/Component/*.cpp")
file(GLOB RENDER "Render/*.h" "Render/*.cpp")
file(GLOB UTILS "Utils/*.h" "Utils/*.cpp")
file(GLOB BASE "Base/*.h" "Base/*.cpp")
file(GLOB AUDIO "Audio/*.h" "Audio/*.cpp")
file(GLOB INPUT "Input/*.h" "Input/*.cpp")

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
add_library(libPe2 STATIC ${ROOT} ${MATH} ${GEOMETRY} ${SCENE} ${RENDER} ${UTILS} ${BASE} ${AUDIO} ${INPUT})
target_include_directories(libPe2 PRIVATE ${CMAKE_SOURCE_DIR}/libPe2 
                                          ${CMAKE_SOURCE_DIR}/libPe2/Audio 
                                          ${CMAKE_SOURCE_DIR}/libPe2/Base 
                                          ${CMAKE_SOURCE_DIR}/libPe2/Input
                                          ${CMAKE_SOURCE_DIR}/libPe2/Math
                                          ${CMAKE_SOURCE_DIR}/libPe2/Render
                                          ${CMAKE_SOURCE_DIR}/libPe2/Scene/Component
                                          ${CMAKE_SOURCE_DIR}/libPe2/Scene)
target_link_libraries(libPe2 PRIVATE SDL2::SDL2 SDL2::SDL2main spdlog::spdlog spdlog::spdlog_header_only glad::glad SDL2::SDL2_ttf)