cmake_minimum_required(VERSION 3.18)
project(coconut C CXX)

set(CMAKE_CXX_STANDARD 14)

######################## Name Setting ########################

set(SRC_DIR src)
set(THIRD_PARTY_DIR 3rdparty)
set(TEST_DIR testing)
set(ENTRY_FILE ${SRC_DIR}/jvm_entry.cc)

set(LIB_NAME coconut_runtime)

set(TEST_TARGET cocotest)

######################## File Globbin ########################

file(GLOB_RECURSE SOURCES
        ${SRC_DIR}/bytecode/*.cc
        ${SRC_DIR}/classloader/*.cc
        ${SRC_DIR}/env/*.cc
        ${SRC_DIR}/rtda/*.cc
        ${SRC_DIR}/utils/*.cc
        ${SRC_DIR}/vm/*.cc
    )
file(GLOB_RECURSE THIRD_PARTY ${THIRD_PARTY_DIR}/*.c)
file(GLOB_RECURSE TESTS ${TEST_DIR}/*.cc)

######################## Target ########################

# IMPORTANT!!!
# 3rdparty: utf16 should be treadted as CXX source
# Otherwise, linking will throw error!
set_source_files_properties(${THIRD_PARTY_DIR}/utf16/converter.c PROPERTIES LANGUAGE CXX)

add_library(${LIB_NAME} STATIC ${THIRD_PARTY} ${SOURCES} )
target_include_directories(${LIB_NAME} PRIVATE ${THIRD_PARTY_DIR})

add_executable(${PROJECT_NAME} ${ENTRY_FILE})
target_link_libraries(${PROJECT_NAME} ${LIB_NAME})
target_compile_options(${PROJECT_NAME} PUBLIC -O2)
target_include_directories(${PROJECT_NAME} PRIVATE ${THIRD_PARTY_DIR})

######################## Testing ########################

# Using 'make cocotest' to make test

option(USE_GTEST "Use GoogleTest for C++ sanity tests" ON) # Whether to use GTest

find_package(GTest)

if(GTEST_FOUND)
    # Include GTEST
    include_directories(${GTEST_INCLUDE_DIRS})
    # MESSAGE(${GTEST_BOTH_LIBRARIES})
    # MESSAGE(${GTEST_LIBRARIES})
    # MESSAGE(${GTEST_MAIN_LIBRARIES})

    # Compile Test

    # need to link pthread lib
    find_package(Threads)

    add_executable(${TEST_TARGET} ${TESTS})
    target_link_libraries(${TEST_TARGET} ${LIB_NAME})
    target_link_libraries(${TEST_TARGET} gtest gtest_main)
    target_link_libraries(${TEST_TARGET} ${CMAKE_THREAD_LIBS_INIT})
    target_include_directories(${TEST_TARGET} PRIVATE ${THIRD_PARTY_DIR})
    target_compile_options(${TEST_TARGET} PUBLIC -O2)
endif()
