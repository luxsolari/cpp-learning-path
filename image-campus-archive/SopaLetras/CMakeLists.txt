cmake_minimum_required(VERSION 3.0.0)
project(SopaLetras VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(SopaLetras main.cpp utiles.cpp utiles.h structs.h tematicas.h "globals.h" )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
include(CPack)
