file(GLOB SRC *.cpp)
add_library(geometry STATIC ${SRC})

target_link_libraries(geometry PUBLIC SeparatedValues)

target_compile_features(geometry PUBLIC cxx_std_20)

target_include_directories(geometry PUBLIC 
	${PROJECT_SOURCE_DIR}/src
)

add_subdirectory(SeparatedValues)

