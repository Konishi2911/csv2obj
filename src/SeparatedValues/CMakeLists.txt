file(GLOB Source *.cpp)

add_library( SeparatedValues STATIC ${Source})


target_include_directories(
    SeparatedValues PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options( SeparatedValues PUBLIC -Wall)

target_compile_features( SeparatedValues PUBLIC cxx_std_17)




