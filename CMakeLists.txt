cmake_minimum_required(VERSION 3.14)
project(TritSet)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(TritSet_run ${SOURCE_FILES})

include_directories(TritSet_lib Google_tests/googletest/googletest/include)
add_subdirectory(TritSet_lib)

target_link_libraries(TritSet_run TritSet_lib)

add_subdirectory(Google_tests)