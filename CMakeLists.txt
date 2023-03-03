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

# This is for our testing framework,
# we don't add REQUIRED because it's just for testing.
# People who might want to build the project to use it should not be required
# to install testing dependencies.
# find_package(GTest)

# if(GTEST_FOUND)
#   add_executable(unit_tests ${sources_test} ${sources})

#   # This define is added to prevent collision with the main.
#   # It might be better solved by not adding the source with the main to the
#   # testing target.
#   target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

#   # This allows us to use the executable as a link library, and inherit all
#   # linker options and library dependencies from it, by simply adding it as dependency.
#   set_target_properties(example PROPERTIES ENABLE_EXPORTS on)

#   target_link_libraries(unit_tests PUBLIC
#     ${GTEST_BOTH_LIBRARIES}
#     example
#   )

#   target_include_directories(unit_tests PUBLIC
#     ${GTEST_INCLUDE_DIRS} # doesn't do anything on linux
#   )

# endif()
