file(GLOB ROOT "*.h" "*.cpp")
file(GLOB MATH "Math/*.h" "Math/*.cpp")
file(GLOB GEOMETRY "Math/Geometry/*.h" "Math/Geometry/*.cpp")
file(GLOB SCENE "Scene/*.h" "Scene/*.cpp")
file(GLOB COMPONENT "Scene/Component/*.h" "Scene/Component/*.cpp")
file(GLOB GRAPHICS "Graphics/*.h" "Graphics/*.cpp")
file(GLOB GL "Graphics/GL/*.h" "Graphics/GL/*.cpp")
file(GLOB INPUT "Input/*.h" "Input/*.cpp")

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
add_library(libmulberry STATIC ${ROOT} ${MATH} ${GEOMETRY} ${SCENE} ${COMPONENT} ${GRAPHICS} ${GL} ${BASE} ${INPUT})
target_include_directories(libmulberry PRIVATE ${CMAKE_SOURCE_DIR}/libmulberry 
                                          ${CMAKE_SOURCE_DIR}/libmulberry/Input
                                          ${CMAKE_SOURCE_DIR}/libmulberry/Math
                                          ${CMAKE_SOURCE_DIR}/libmulberry/Graphics
                                          ${CMAKE_SOURCE_DIR}/libmulberry/Graphics/GL
                                          ${CMAKE_SOURCE_DIR}/libmulberry/Scene/Component
                                          ${CMAKE_SOURCE_DIR}/libmulberry/Scene)
target_link_libraries(libmulberry PRIVATE  glm::glm SDL2::SDL2 SDL2::SDL2main spdlog::spdlog spdlog::spdlog_header_only glad::glad SDL2_ttf::SDL2_ttf)