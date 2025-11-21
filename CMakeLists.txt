cmake_minimum_required(VERSION 3.14)
project(fiveLab)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(lab
    src/main.cpp
    src/allocator.cpp
)

add_executable(Test
    test/mainTest.cpp
    test/testF.cpp
    src/allocator.cpp
)

target_include_directories(lab PRIVATE include inline)
target_include_directories(lab PRIVATE include inline)

target_link_libraries(Test GTest::GTest GTest::Main)
target_include_directories(Test PRIVATE include)