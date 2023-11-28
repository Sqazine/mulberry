file(GLOB SRC "*.h" "*.cpp")

set(EXE_NAME Asteroid)

add_executable(${EXE_NAME} ${SRC})
target_include_directories(${EXE_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(${EXE_NAME} PRIVATE mulberry)
target_compile_definitions(${EXE_NAME} PRIVATE ${CURRENT_PLATFORM})