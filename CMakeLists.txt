cmake_minimum_required(VERSION 3.29)
project(ElaboratoLab)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(ElaboratoLab main.cpp
        User.h
        Message.h
        Chat.h
        ChatRegistry.cpp
        ChatRegistry.h
)

add_executable(my_tests test.cpp
        ChatRegistry.cpp

)

target_link_libraries(my_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(my_tests)
