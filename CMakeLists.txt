cmake_minimum_required(VERSION 3.10)

project(ExpCalculator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed. Please use an out-of-source build directory.")
endif()

if(NOT CMAKE_BINARY_DIR)
    set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
endif()


add_library(exp_calculator
    src/exp_calculator/exp_calculator.cpp
    src/exp_calculator/token.cpp
    src/exp_calculator/token_stream.cpp
    src/exp_calculator/variable_table.cpp
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

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()
add_subdirectory(googletest)
add_executable(test_app tests/test_main.cpp) 
target_link_libraries(test_app gtest_main)
target_link_libraries(test_app exp_calculator)

add_test(NAME MyTest COMMAND test_app)

add_custom_target(run
    COMMAND main
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/output
)