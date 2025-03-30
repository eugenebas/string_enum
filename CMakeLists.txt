cmake_minimum_required(VERSION 3.16)

project("string_enum" LANGUAGES CXX)
enable_testing()
include(GNUInstallDirs)

if(NOT DEFINED STRING_ENUM_MAX_SIZE)
    set(STRING_ENUM_MAX_SIZE 255)
endif()

message(STATUS "Building ${CMAKE_PROJECT_NAME} with STRING_ENUM_MAX_SIZE set to ${STRING_ENUM_MAX_SIZE}")
message(STATUS "CMAKE_INSTALL_PREFIX: '${CMAKE_INSTALL_PREFIX}'")

set(CMAKE_CXX_STANDARD 20)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")

add_subdirectory(string_enum)
add_subdirectory(tests)

set(CPACK_PACKAGE_CONTACT "noreply@nomail.com")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "")

include(CPack)
