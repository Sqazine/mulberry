add_subdirectory(Asteroid)
add_subdirectory(Sprite)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})