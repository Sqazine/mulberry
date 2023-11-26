file(GLOB SRC "*.h" "*.cpp")

add_library(stb STATIC ${SRC})
if(MSVC)
    target_compile_options(stb PRIVATE "/wd4251;")
endif()