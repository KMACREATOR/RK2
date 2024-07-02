cmake_minimum_required(VERSION 3.10)


project(RK2)

add_executable(FactoryMethod FactoryMethod.cpp)



set(GTEST_ROOT gtest/googletest)
set(GMOCK_ROOT gtest/googlemock)

add_subdirectory(${GTEST_ROOT} gtest)
target_link_libraries(RK2 \${PROJECT_NAME} gtest_main)

include_directories(\${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()
add_test(NAME check COMMAND check)
