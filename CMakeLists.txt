cmake_minimum_required(VERSION 3.0)

project("string_enum")

if(NOT DEFINED STRING_ENUM_MAX_SIZE)
    set(STRING_ENUM_MAX_SIZE 255)
endif()
message(STATUS "Building ${CMAKE_PROJECT_NAME} with STRING_ENUM_MAX_SIZE set to ${STRING_ENUM_MAX_SIZE}")

# generate get_nth_arg.hpp
set(INDEX 0)
set(__STR_ENUM_GET_NTH_ARG_ARGS "")
while(STRING_ENUM_MAX_SIZE GREATER_EQUAL INDEX)
    string(APPEND __STR_ENUM_GET_NTH_ARG_ARGS " _${INDEX}, ")
    math(EXPR INDEX "${INDEX}+1")
endwhile()
set(__STR_ENUM_GET_NTH_ARG_ARGS "${__STR_ENUM_GET_NTH_ARG_ARGS}")
configure_file(get_nth_arg.hpp.in get_nth_arg.hpp)

# generate count_args.hpp
set(INDEX ${STRING_ENUM_MAX_SIZE})
set(__STR_ENUM_COUNT_ARGS_ARGS "")
while(INDEX GREATER 0)
    string(APPEND __STR_ENUM_COUNT_ARGS_ARGS " ${INDEX}")
    if(NOT INDEX EQUAL 1)
        string(APPEND __STR_ENUM_COUNT_ARGS_ARGS ", ")
    endif()
    math(EXPR INDEX "${INDEX}-1")
endwhile()
configure_file(count_args.hpp.in count_args.hpp)

# generate generate_strings.hpp
set(INDEX 0)
set(__STR_ENUM__GENERATE_STRINGS_OVERLOAD_DEFINES "")
while(STRING_ENUM_MAX_SIZE GREATER_EQUAL INDEX)
    math(EXPR NEXT_INDEX "${INDEX}+1")
    string(APPEND __STR_ENUM__GENERATE_STRINGS_OVERLOAD_DEFINES "#define __STR_ENUM__GENERATE_STRINGS${NEXT_INDEX}(element, ...) #element")
    if(INDEX GREATER 0)
        string(APPEND __STR_ENUM__GENERATE_STRINGS_OVERLOAD_DEFINES ", __STR_ENUM__GENERATE_STRINGS${INDEX}(__VA_ARGS__)\n")
    else()
        string(APPEND __STR_ENUM__GENERATE_STRINGS_OVERLOAD_DEFINES "\n")
    endif()
    set(INDEX ${NEXT_INDEX})
endwhile()

set(INDEX ${STRING_ENUM_MAX_SIZE})
set(__STR_ENUM__GENERATE_STRINGS_OVERLOADS "")
while(INDEX GREATER 0)
    string(APPEND __STR_ENUM__GENERATE_STRINGS_OVERLOADS "__STR_ENUM__GENERATE_STRINGS${INDEX}")
    if(NOT INDEX EQUAL 1)
        string(APPEND __STR_ENUM__GENERATE_STRINGS_OVERLOADS ", ")
    endif()
    math(EXPR INDEX "${INDEX}-1")
endwhile()
configure_file(generate_strings.hpp.in generate_strings.hpp)

# generate generate_constants.hpp
set(INDEX 0)
set(__STR_ENUM__GENERATE_CONSTANTS__OVERLOAD_DEFINES "")
while(STRING_ENUM_MAX_SIZE GREATER_EQUAL INDEX)
    math(EXPR NEXT_INDEX "${INDEX}+1")
    string(APPEND __STR_ENUM__GENERATE_CONSTANTS__OVERLOAD_DEFINES "#define __STR_ENUM_GENERATE_CONSTANTS${NEXT_INDEX}(enum_name, element, ...) __STR_ENUM_GENERATE_CONSTANT(enum_name, element) __STR_ENUM_GENERATE_CONSTANTS${INDEX}(enum_name, __VA_ARGS__)\n")
    set(INDEX ${NEXT_INDEX})
endwhile()

set(INDEX ${STRING_ENUM_MAX_SIZE})
set(__STR_ENUM__GENERATE_CONSTANTS__OVERLOADS "")
while(INDEX GREATER 0)
    string(APPEND __STR_ENUM__GENERATE_CONSTANTS__OVERLOADS "__STR_ENUM_GENERATE_CONSTANTS${INDEX}")
    if(NOT INDEX EQUAL 1)
        string(APPEND __STR_ENUM__GENERATE_CONSTANTS__OVERLOADS ", ")
    endif()
    math(EXPR INDEX "${INDEX}-1")
endwhile()
configure_file(generate_constants.hpp.in generate_constants.hpp)

set (CMAKE_CXX_STANDARD 20)
add_library(${CMAKE_PROJECT_NAME} INTERFACE string_enum.hpp names.hpp get_nth_arg.hpp)
target_include_directories(${CMAKE_PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_BINARY_DIR}"
                                                           "${CMAKE_CURRENT_SOURCE_DIR}")
target_sources(${CMAKE_PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_BINARY_DIR}/get_nth_arg.hpp"
                                               "${CMAKE_CURRENT_BINARY_DIR}/count_args.hpp"
                                               "${CMAKE_CURRENT_BINARY_DIR}/generate_strings.hpp"
                                               "${CMAKE_CURRENT_BINARY_DIR}/generate_constants.hpp")

add_executable(test main.cpp)
target_link_libraries(test ${CMAKE_PROJECT_NAME})
