set(VULKAN_ROOT "$ENV{VULKAN_SDK}" CACHE STRING "")
message(STATUS ${VULKAN_ROOT})


file(GLOB ROOT "*.h" "*.cpp")
file(GLOB CORE "Core/*.h" "Core/*.cpp")
file(GLOB MATH "Math/*.h" "Math/*.cpp")
file(GLOB PLATFORM "Platform/*.h" "Platform/*.cpp")
file(GLOB PLATFORM_SDL2_WRAPPER "Platform/SDL2/*.h" "Platform/SDL2/*.cpp")
file(GLOB SCENE "Scene/*.h" "Scene/*.cpp")
file(GLOB COMPONENT "Scene/Component/*.h" "Scene/Component/*.cpp")
file(GLOB GRAPHICS "Graphics/*.h" "Graphics/*.cpp")
file(GLOB RHI "Graphics/RHI/*.h" "Graphics/RHI/*.cpp")
file(GLOB GL "Graphics/RHI/GL/*.h" "Graphics/RHI/GL/*.cpp")
file(GLOB VK "Graphics/RHI/VK/*.h" "Graphics/RHI/VK/*.cpp")

source_group("" FILES ${ROOT})
source_group("Core" FILES ${CORE})
source_group("Math" FILES ${MATH})
source_group("Platform" FILES ${PLATFORM})
source_group("Platform/SDL2" FILES ${PLATFORM_SDL2_WRAPPER})
source_group("Scene" FILES ${SCENE})
source_group("Scene/Component" FILES ${COMPONENT})
source_group("Graphics" FILES ${GRAPHICS})
source_group("Graphics/RHI" FILES ${RHI})
source_group("Graphics/RHI/GL" FILES ${GL})
source_group("Graphics/RHI/VK" FILES ${VK})

find_package(glslang CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
add_library(libmulberry STATIC ${ROOT} ${CORE} ${MATH} ${PLATFORM} ${PLATFORM_SDL2_WRAPPER} ${SCENE} ${COMPONENT} ${GRAPHICS} ${RHI} ${GL} ${VK})
target_include_directories(libmulberry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} 
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Core
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Math
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Platform
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Platform/SDL2
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Graphics
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/RHI/GL
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/RHI/VK
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/RHI
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Component
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Scene
                                          ${VULKAN_ROOT}/Include)
target_link_libraries(libmulberry PRIVATE  glm::glm SDL2::SDL2 SDL2::SDL2main spdlog::spdlog spdlog::spdlog_header_only glad::glad SDL2_ttf::SDL2_ttf glslang::OSDependent glslang::glslang glslang::MachineIndependent glslang::GenericCodeGen glslang::OGLCompiler glslang::glslang-default-resource-limits glslang::SPVRemapper glslang::SPIRV glslang::HLSL ${VULKAN_ROOT}/Lib/vulkan-1.lib)

message(STATUS "operation system is ${CMAKE_SYSTEM}")
 
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "current platform: Linux")
    target_compile_definitions(libmulberry PRIVATE PLATFORM_LINUX)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "current platform: Windows")
    target_compile_definitions(libmulberry PRIVATE PLATFORM_WINDOWS)
elseif (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    message(STATUS "current platform: FreeBSD")
    target_compile_definitions(libmulberry PRIVATE PLATFORM_FREEBSD)
else ()
    message(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
    target_compile_definitions(libmulberry PRIVATE PLATFORM_OTHER)
endif (CMAKE_SYSTEM_NAME MATCHES "Linux")