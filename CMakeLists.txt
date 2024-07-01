cmake_minimum_required(VERSION 3.10)


project(RK2)

enable_testing()

add_executable(FactoryMethod FactoryMethod.cpp)

set(GTEST_ROOT /path/to/gtest)
set(GMOCK_ROOT /path/to/gmock)

add_subdirectory(${GTEST_ROOT} gtest)
add_subdirectory(${GMOCK_ROOT} gmock)
enable_testing()
add_test(NAME check COMMAND check)
