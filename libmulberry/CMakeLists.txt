set(VULKAN_ROOT "$ENV{VULKAN_SDK}" CACHE STRING "")
message(STATUS ${VULKAN_ROOT})


file(GLOB ROOT "*.h" "*.cpp")
file(GLOB CORE "Core/*.h" "Core/*.cpp")
file(GLOB MATH "Math/*.h" "Math/*.cpp")
file(GLOB SCENE "Scene/*.h" "Scene/*.cpp")
file(GLOB COMPONENT "Scene/Component/*.h" "Scene/Component/*.cpp")
file(GLOB GRAPHICS "Graphics/*.h" "Graphics/*.cpp")
file(GLOB GL "Graphics/GL/*.h" "Graphics/GL/*.cpp")
file(GLOB VK "Graphics/VK/*.h" "Graphics/VK/*.cpp")

source_group("" FILES ${ROOT})
source_group("Core" FILES ${CORE})
source_group("Math" FILES ${MATH})
source_group("Scene" FILES ${SCENE})
source_group("Scene/Component" FILES ${COMPONENT})
source_group("Graphics" FILES ${GRAPHICS})
source_group("Graphics/GL" FILES ${GL})
source_group("Graphics/VK" FILES ${VK})

find_package(glslang CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
add_library(libmulberry STATIC ${ROOT} ${CORE} ${MATH} ${SCENE} ${COMPONENT} ${GRAPHICS} ${GL} ${VK})
target_include_directories(libmulberry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} 
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Core
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Math
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Graphics
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/GL
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/VK
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Component
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Scene
                                          ${VULKAN_ROOT}/Include)
target_link_libraries(libmulberry PRIVATE  glm::glm SDL2::SDL2 SDL2::SDL2main spdlog::spdlog spdlog::spdlog_header_only glad::glad SDL2_ttf::SDL2_ttf glslang::OSDependent glslang::glslang glslang::MachineIndependent glslang::GenericCodeGen glslang::OGLCompiler glslang::glslang-default-resource-limits glslang::SPVRemapper glslang::SPIRV glslang::HLSL ${VULKAN_ROOT}/Lib/vulkan-1.lib)