set(CMAKE_CXX_STANDART 11)

project(promise_future)
cmake_minimum_required(VERSION 3.2)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_definitions(-D_GTEST)
add_definitions(-D_GLIBCXX_DEBUG)

file(GLOB_RECURSE SOURCE_FILES source/*.cpp testsAlex/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.h testsAlex/*.h)

include_directories(include)

if ("$ENV{GTEST}" STREQUAL "y")
    message("!Gtests're enabled!")

    find_package(GTest REQUIRED)

    include_directories(testsAlex)
    add_definitions(-D_GTEST)
endif ()

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

if ("$ENV{GTEST}" STREQUAL "y")
    target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} gmock)
endif ()

target_link_libraries(${PROJECT_NAME} gtest gtest_main)
target_link_libraries(${PROJECT_NAME} pthread)
