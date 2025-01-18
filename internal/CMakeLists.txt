include(cmake/generate_nth_arg.cmake)
include(cmake/generate_count_args.cmake)
include(cmake/generate_strings.cmake)
include(cmake/generate_constants.cmake)

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

add_library(internal INTERFACE)
target_include_directories(internal INTERFACE "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
set(INTERNAL_HEADERS "names.hpp"
                     "${CMAKE_CURRENT_BINARY_DIR}/get_nth_arg.hpp"
                     "${CMAKE_CURRENT_BINARY_DIR}/count_args.hpp"
                     "${CMAKE_CURRENT_BINARY_DIR}/generate_strings.hpp"
                     "${CMAKE_CURRENT_BINARY_DIR}/generate_constants.hpp")
target_sources(internal INTERFACE ${INTERNAL_HEADERS})
set_target_properties(internal PROPERTIES PRIVATE_HEADER "${INTERNAL_HEADERS}")
install(TARGETS internal PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}/internal")

add_subdirectory(tests)
