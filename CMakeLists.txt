cmake_minimum_required(VERSION 3.18)
project(coconut C CXX)

set(CMAKE_CXX_STANDARD 17)

# File Globbing

set(SRC_DIR src)
set(THIRD_PARTY_DIR 3rdparty)

file(GLOB_RECURSE SOURCES       ${SRC_DIR}/*.cc)
file(GLOB_RECURSE THIRD_PARTY ${THIRD_PARTY_DIR}/*.c)
# file(GLOB_RECURSE TESTS testing/*.cpp)

# Target

# IMPORTANT!!!
# 3rdparty: utf16 should be treadted as CXX source
# Otherwise, linking will throw error!
set_source_files_properties(${THIRD_PARTY_DIR}/utf16/converter.c PROPERTIES LANGUAGE CXX)

add_executable(${PROJECT_NAME} ${THIRD_PARTY} ${SOURCES})
target_compile_options(${PROJECT_NAME} PUBLIC -O2)
target_include_directories(${PROJECT_NAME} PRIVATE ${THIRD_PARTY_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${SRC_DIR})


# Testing


# find_package(GTest)

# if(GTEST_FOUND)
#   TODO

# endif()
