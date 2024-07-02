cmake_minimum_required(VERSION 3.10)


project(RK2)

add_executable(FactoryMethod FactoryMethod.cpp)



set(GTEST_ROOT third-party/gtest/googletest)
set(GMOCK_ROOT third-party/gtest/googlemock)

add_subdirectory(${GTEST_ROOT} gtest)
add_subdirectory(${GMOCK_ROOT} gmock)

target_link_libraries(RK2 gtest gmock)

enable_testing()
add_test(NAME check COMMAND check)
