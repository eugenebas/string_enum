cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(internal)

add_library(${CMAKE_PROJECT_NAME} INTERFACE)
target_include_directories(${CMAKE_PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_BINARY_DIR}"
                                                           "${CMAKE_CURRENT_SOURCE_DIR}")

set(API_HEADERS "string_enum.hpp")
target_sources(${CMAKE_PROJECT_NAME} INTERFACE ${API_HEADERS})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${API_HEADERS}")

install(TARGETS ${CMAKE_PROJECT_NAME} PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}")
