#include <gtest/gtest.h>
#include <internal/inner_string_array.hpp>

TEST(inner_string_array_tests, generate_array) {
    __STR_ENUM__INNER_STRING_ARRAY(Animals, DOG, CAT, COW);
    EXPECT_EQ(__hidden_array_Animals.size(), 3);
    EXPECT_EQ(__hidden_array_Animals[0], "DOG");
    EXPECT_EQ(__hidden_array_Animals[1], "CAT");
    EXPECT_EQ(__hidden_array_Animals[2], "COW");
}
