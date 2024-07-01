set(LIB_NAME libmulberry)
if(CURRENT_PLATFORM STREQUAL "Linux")
    set(LIB_NAME mulberry)
endif()

file(GLOB ROOT "*.h" "*.cpp" "*.inl")
file(GLOB CORE "Core/*.h" "Core/*.cpp" "Core/*.inl")
file(GLOB MATH "Math/*.h" "Math/*.cpp" "Math/*.inl")
file(GLOB PLATFORM "Platform/*.h" "Platform/*.cpp" "Platform/*.inl")
file(GLOB PLATFORM_SDL2_WRAPPER "Platform/SDL2/*.h" "Platform/SDL2/*.cpp" "Platform/SDL2/*.inl")
file(GLOB SCENE "Scene/*.h" "Scene/*.cpp" "Scene/*.inl")
file(GLOB COMPONENT "Scene/Component/*.h" "Scene/Component/*.cpp" "Scene/Component/*.inl")
file(GLOB GRAPHICS "Graphics/*.h" "Graphics/*.cpp" "Graphics/*.inl")
file(GLOB RHI "Graphics/RHI/*.h" "Graphics/RHI/*.cpp" "Graphics/RHI/*.inl")
file(GLOB VK "Graphics/RHI/VK/*.h" "Graphics/RHI/VK/*.cpp" "Graphics/RHI/VK/*.inl")

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

add_library(${LIB_NAME} STATIC ${ROOT} ${CORE} ${MATH} ${PLATFORM} ${PLATFORM_SDL2_WRAPPER} ${SCENE} ${COMPONENT} ${GRAPHICS} ${RHI} ${VK})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} 
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
                             

target_link_libraries(${LIB_NAME} PRIVATE  SDL2-static
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
                                        
target_compile_definitions(${LIB_NAME} PRIVATE ${CURRENT_PLATFORM})

if(MSVC)
    target_compile_definitions(${LIB_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(${LIB_NAME} PRIVATE _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)
    target_compile_definitions(${LIB_NAME} PRIVATE NOMINMAX)
    target_compile_options(${LIB_NAME} PRIVATE "/W4")
    target_compile_options(${LIB_NAME} PRIVATE "/wd4251;")
    target_compile_options(${LIB_NAME} PRIVATE "/wd4201;")
endif()