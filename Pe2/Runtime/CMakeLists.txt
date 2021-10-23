file(GLOB ROOT "*.h" "*.cpp")
file(GLOB MATH "Math/*.h" "Math/*.cpp")
file(GLOB SYSTEM "System/*.h" "System/*.cpp")

find_package(SDL2 CONFIG REQUIRED)

add_library(Pe2 STATIC ${ROOT} ${MATH} ${SYSTEM})
target_include_directories(Pe2 PRIVATE ${ROOT} ${MATH} ${SYSTEM})
target_link_libraries(Pe2 PRIVATE SDL2::SDL2 SDL2::SDL2main)