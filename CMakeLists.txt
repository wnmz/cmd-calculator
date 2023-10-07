cmake_minimum_required(VERSION 3.10)

project(ExpCalculator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed. Please use an out-of-source build directory.")
endif()

if(NOT CMAKE_BINARY_DIR)
    set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
endif()


add_library(exp_calculator
    src/exp_calculator/exp_calculator.cpp
    src/exp_calculator/token_stream.cpp
)

target_include_directories(exp_calculator
    PUBLIC
        src/exp_calculator
)

add_executable(main
    src/main.cpp
)

target_link_libraries(main
    PRIVATE
        exp_calculator
)

# Testing
enable_testing()
add_subdirectory(googletest)
add_executable(test_app tests/test_main.cpp) 
target_link_libraries(test_app gtest_main)

add_test(NAME MyTest COMMAND test_app)