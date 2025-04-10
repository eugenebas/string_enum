include(GoogleTest)

find_package(GTest REQUIRED)

add_executable(count_args_tests count_args_tests.cpp)
target_include_directories(count_args_tests PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(count_args_tests GTest::GTest GTest::Main ${CMAKE_PROJECT_NAME})
gtest_discover_tests(count_args_tests)

add_executable(names_tests names_tests.cpp)
target_include_directories(names_tests PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(names_tests GTest::GTest GTest::Main ${CMAKE_PROJECT_NAME})
gtest_discover_tests(names_tests)

add_executable(inner_string_array_tests inner_string_array_tests.cpp)
target_include_directories(inner_string_array_tests PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(inner_string_array_tests GTest::GTest GTest::Main ${CMAKE_PROJECT_NAME})
gtest_discover_tests(inner_string_array_tests)

add_executable(inner_enum_class_tests inner_enum_class_tests.cpp)
target_include_directories(inner_enum_class_tests PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(inner_enum_class_tests GTest::GTest GTest::Main ${CMAKE_PROJECT_NAME})
gtest_discover_tests(inner_enum_class_tests)
