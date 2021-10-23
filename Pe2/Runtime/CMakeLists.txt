file(GLOB ROOT "*.h" "*.cpp")
file(GLOB MATH "Math/*.h" "Math/*.cpp")
file(GLOB SYSTEM "System/*.h" "System/*.cpp")

add_library(Pe2 STATIC ${ROOT} ${MATH} ${SYSTEM})