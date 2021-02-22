add_executable(csv2obj csv2obj.cpp)

target_link_libraries(csv2obj PUBLIC geometry)

target_include_directories(csv2obj PUBLIC ${PROJECT_SOURCE_DIR}/src/)

target_compile_features(csv2obj PUBLIC cxx_std_17)


install(
    TARGETS csv2obj
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

