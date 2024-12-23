cmake_minimum_required(VERSION 3.16)

project("string_enum" LANGUAGES CXX)

include(GNUInstallDirs)
include(GoogleTest)

if(NOT DEFINED STRING_ENUM_MAX_SIZE)
    set(STRING_ENUM_MAX_SIZE 255)
endif()

message(STATUS "Building ${CMAKE_PROJECT_NAME} with STRING_ENUM_MAX_SIZE set to ${STRING_ENUM_MAX_SIZE}")
message(STATUS "CMAKE_INSTALL_PREFIX: '${CMAKE_INSTALL_PREFIX}'")

add_subdirectory(internal)

set(CMAKE_CXX_STANDARD 20)
add_library(${CMAKE_PROJECT_NAME} INTERFACE)
target_include_directories(${CMAKE_PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_BINARY_DIR}"
                                                           "${CMAKE_CURRENT_SOURCE_DIR}")

set(API_HEADERS "string_enum.hpp")
target_sources(${CMAKE_PROJECT_NAME} INTERFACE ${API_HEADERS})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${API_HEADERS}")

enable_testing()
find_package(GTest REQUIRED)

add_executable(unit_tests tests.cpp)
target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(unit_tests GTest::GTest GTest::Main ${CMAKE_PROJECT_NAME})

gtest_discover_tests(unit_tests)

install(TARGETS ${CMAKE_PROJECT_NAME} PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}")
