cmake_minimum_required(VERSION 3.15)
project(Filesystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.4.0 
)
FetchContent_MakeAvailable(Catch2)

add_library(my_source_lib 
    src/Inode.cc
)

target_include_directories(my_source_lib PUBLIC include)

add_executable(unit_tests
    tests/test_inode.cc
)

target_link_libraries(unit_tests
    PRIVATE
        Catch2::Catch2WithMain
        my_source_lib
)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)
