cmake_minimum_required(VERSION 2.8.12)

PROJECT(HeatEquation)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

ADD_SUBDIRECTORY(src/params)
ADD_SUBDIRECTORY(src/grid)

ADD_EXECUTABLE(HeatEquation src/main.cpp)

ADD_DEPENDENCIES(HeatEquation params grid)

TARGET_LINK_LIBRARIES(HeatEquation params grid dl m)
