cmake_minimum_required(VERSION 3.10)

option(BUILD_SAMPLES ON)

set(PROJECT_NAME Algebra_of_polynomials)
project(${PROJECT_NAME})

include(CTest)
enable_testing()  # defines BUILD_TESTING

set(MP2_TESTS   "test_${PROJECT_NAME}")
set(MP2_CUSTOM_PROJECT "${PROJECT_NAME}")
set(MP2_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(include)

if(BUILD_TESTING)
	add_subdirectory(test)
	add_subdirectory(3rdparty/googletest)
	include_directories(3rdparty/googletest/googletest/include)
endif()


# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME}")
message( STATUS "======================================")
message( STATUS "")
message( STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message( STATUS "")

