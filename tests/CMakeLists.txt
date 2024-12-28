include(GoogleTest)

find_package(GTest REQUIRED)

add_executable(string_enum_tests string_enum_tests.cpp)
target_include_directories(string_enum_tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(string_enum_tests GTest::GTest GTest::Main ${CMAKE_PROJECT_NAME})

gtest_discover_tests(string_enum_tests)
