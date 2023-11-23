set(EXE_NAME Sprite)

add_executable(${EXE_NAME} main.cpp)
target_include_directories(${EXE_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(${EXE_NAME} PRIVATE mulberry)
target_compile_definitions(${EXE_NAME} PRIVATE RESOURCES_DIR="${CMAKE_SOURCE_DIR}/tests/Assets/")
target_compile_definitions(${EXE_NAME} PRIVATE ${CURRENT_PLATFORM})