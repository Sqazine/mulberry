file(GLOB ROOT "*.h" "*.cpp")
file(GLOB CORE "Core/*.h" "Core/*.cpp")
file(GLOB MATH "Math/*.h" "Math/*.cpp")
file(GLOB PLATFORM "Platform/*.h" "Platform/*.cpp")
file(GLOB PLATFORM_SDL2_WRAPPER "Platform/SDL2/*.h" "Platform/SDL2/*.cpp")
file(GLOB SCENE "Scene/*.h" "Scene/*.cpp")
file(GLOB COMPONENT "Scene/Component/*.h" "Scene/Component/*.cpp")
file(GLOB GRAPHICS "Graphics/*.h" "Graphics/*.cpp")
file(GLOB RHI "Graphics/RHI/*.h" "Graphics/RHI/*.cpp")
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
source_group("Graphics/RHI/VK" FILES ${VK})

add_library(mulberry STATIC ${ROOT} ${CORE} ${MATH} ${PLATFORM} ${PLATFORM_SDL2_WRAPPER} ${SCENE} ${COMPONENT} ${GRAPHICS} ${RHI} ${VK})
target_include_directories(mulberry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} 
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Core
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Math
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Platform
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Platform/SDL2
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Graphics
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/RHI/VK
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/RHI
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Scene/Component
                                          ${CMAKE_CURRENT_SOURCE_DIR}/Scene
                                          ${VULKAN_ROOT}/Include
                                          ${FREETYPE_INC_DIR}
                                          ${SDL_TTF_INC_DIR}
                                          ${SDL_INC_DIR}
                                          ${STB_INC_DIR}
                                          ${SPDLOG_INC_DIR}
                                          ${THIRD_PARTY_DIR}
                                          )

find_library(vulkan_1
             vulkan-1.lib
             PATHS ${VULKAN_ROOT}/Lib)
                             

target_link_libraries(mulberry PRIVATE  SDL2-static
                                        SDL2main 
                                        stb
                                        spdlog::spdlog 
                                        SDL2_ttf 
                                        OSDependent 
                                        glslang 
                                        MachineIndependent 
                                        GenericCodeGen 
                                        OGLCompiler 
                                        glslang-default-resource-limits 
                                        SPVRemapper 
                                        SPIRV 
                                        HLSL 
                                        ${vulkan_1})
                                        
target_compile_definitions(mulberry PRIVATE SHOW_FPS_ON_WINDOW_TITLE)
target_compile_definitions(mulberry PRIVATE ${CURRENT_PLATFORM})

if(MSVC)
    target_compile_definitions(mulberry PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(mulberry PRIVATE _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)
    target_compile_definitions(mulberry PRIVATE NOMINMAX)
    target_compile_options(mulberry PRIVATE "/W4")
    target_compile_options(mulberry PRIVATE "/wd4251;")
    target_compile_options(mulberry PRIVATE "/wd4201;")
endif()