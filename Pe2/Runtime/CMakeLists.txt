
set(VULKAN_ROOT "$ENV{VULKAN_SDK}" CACHE STRING "")
set(VULKAN_INCLUDE_DIR "${VULKAN_ROOT}/Include")
set(VULKAN_LIB_DIR "${VULKAN_ROOT}/Lib")

message("VULKAN_ROOT=${VULKAN_ROOT}")
message("VULKAN_INCLUDE_DIR=${VULKAN_INCLUDE_DIR}")
message("VULKAN_LIB_DIR=${VULKAN_LIB_DIR}")

file(GLOB ROOT "*.h" "*.cpp")
file(GLOB MATH "Math/*.h" "Math/*.cpp")
file(GLOB SYSTEM "System/*.h" "System/*.cpp")
file(GLOB SCENE "Scene/*.h" "Scene/*.cpp")
file(GLOB COMPONENT "Scene/Component/*.h" "Scene/Component/*.cpp")
file(GLOB VULKAN "Graphics/Backend/VK/*.h" "Graphics/Backend/VK/*.cpp")

find_package(SDL2 CONFIG REQUIRED)

add_library(Pe2 STATIC ${ROOT} ${MATH} ${SYSTEM} ${SCENE} ${VULKAN})
target_include_directories(Pe2 PRIVATE ${VULKAN_INCLUDE_DIR} ${ROOT} ${MATH} ${SYSTEM} ${SCENE} ${VULKAN})
target_link_libraries(Pe2 PRIVATE ${VULKAN_LIB_DIR}/vulkan-1.lib SDL2::SDL2 SDL2::SDL2main)