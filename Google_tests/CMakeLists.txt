# 'Google_test' is the subproject name
project(Google_tests)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(Google_Tests_run tests.cpp)

# linking Google_Tests_run with DateConverter_lib which will be tested
target_link_libraries(Google_Tests_run TritSet_lib)

target_link_libraries(Google_Tests_run gtest gtest_main)