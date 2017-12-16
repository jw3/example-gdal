cmake_minimum_required(VERSION 3.9)
project(gdal_test)

set(CMAKE_CXX_STANDARD 11)

find_package(GDAL REQUIRED)

message(STATUS "gdal-lib: ${GDAL_LIBRARY}  gdal-includes: ${GDAL_INCLUDE_DIR}")

add_executable(gdal_test main.cpp)
target_include_directories(gdal_test PRIVATE ${GDAL_INCLUDE_DIR})
target_link_libraries(gdal_test ${GDAL_LIBRARY})
