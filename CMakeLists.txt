cmake_minimum_required(VERSION 3.16)

project("string_enum" LANGUAGES CXX)

include(GNUInstallDirs)
include(GoogleTest)
include(cmake/generate_nth_arg.cmake)
include(cmake/generate_count_args.cmake)
include(cmake/generate_strings.cmake)
include(cmake/generate_constants.cmake)

if(NOT DEFINED STRING_ENUM_MAX_SIZE)
    set(STRING_ENUM_MAX_SIZE 255)
endif()

message(STATUS "Building ${CMAKE_PROJECT_NAME} with STRING_ENUM_MAX_SIZE set to ${STRING_ENUM_MAX_SIZE}")
message(STATUS "CMAKE_INSTALL_PREFIX: '${CMAKE_INSTALL_PREFIX}'")

# generate get_nth_arg.hpp
GENERATE_GET_NTH_ARG_ARGS(${STRING_ENUM_MAX_SIZE} __STR_ENUM_GET_NTH_ARG_ARGS)
configure_file(get_nth_arg.hpp.in get_nth_arg.hpp)

# generate count_args.hpp
GENERATE_COUNT_ARGS_ARGS(${STRING_ENUM_MAX_SIZE} __STR_ENUM_COUNT_ARGS_ARGS)
configure_file(count_args.hpp.in count_args.hpp)

# generate generate_strings.hpp
GENERATE_STRINGS_OVERLOADS(${STRING_ENUM_MAX_SIZE} __STR_ENUM__GENERATE_STRINGS_OVERLOAD_DEFINES)
GENERATE_STRINGS_OVERLOAD_ARGS(${STRING_ENUM_MAX_SIZE} __STR_ENUM__GENERATE_STRINGS_OVERLOADS)
configure_file(generate_strings.hpp.in generate_strings.hpp)

# generate generate_constants.hpp
GENERATE_CONSTANTS_DEFINES(${STRING_ENUM_MAX_SIZE} __STR_ENUM__GENERATE_CONSTANTS__OVERLOAD_DEFINES)
GENERATE_CONSTANTS_OVERLOADS(${STRING_ENUM_MAX_SIZE} __STR_ENUM__GENERATE_CONSTANTS__OVERLOADS)
configure_file(generate_constants.hpp.in generate_constants.hpp)

set(CMAKE_CXX_STANDARD 20)
add_library(${CMAKE_PROJECT_NAME} INTERFACE)
target_include_directories(${CMAKE_PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_BINARY_DIR}"
                                                           "${CMAKE_CURRENT_SOURCE_DIR}")

set(INTERNAL_HEADERS "names.hpp"
                     "${CMAKE_CURRENT_BINARY_DIR}/get_nth_arg.hpp"
                     "${CMAKE_CURRENT_BINARY_DIR}/count_args.hpp"
                     "${CMAKE_CURRENT_BINARY_DIR}/generate_strings.hpp"
                     "${CMAKE_CURRENT_BINARY_DIR}/generate_constants.hpp")
set(API_HEADERS "string_enum.hpp")

target_sources(${CMAKE_PROJECT_NAME} INTERFACE ${INTERNAL_HEADERS} ${API_HEADERS})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES PUBLIC_HEADER  "${API_HEADERS}"
                                                       PRIVATE_HEADER "${INTERNAL_HEADERS}")

enable_testing()
find_package(GTest REQUIRED)

add_executable(unit_tests tests.cpp)
target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(unit_tests GTest::GTest GTest::Main ${CMAKE_PROJECT_NAME})

gtest_discover_tests(unit_tests)

install(TARGETS ${CMAKE_PROJECT_NAME} PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}"
                                      PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}/internal")
