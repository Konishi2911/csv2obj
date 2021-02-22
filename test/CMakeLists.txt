add_executable(csvExtruderTest csvExtruderTest.cpp)

target_link_libraries(csvExtruderTest PRIVATE geometry)

target_compile_features(csvExtruderTest PUBLIC cxx_std_17)

target_include_directories(csvExtruderTest PUBLIC ${PROJECT_SOURCE_DIR}/src/)
