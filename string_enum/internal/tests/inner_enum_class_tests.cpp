#include <gtest/gtest.h>
#include <internal/inner_enum_class.hpp>

TEST(inner_enum_class_tests, generate_enum_class) {
   __STR_ENUM__INNER_ENUM_CLASS(Animals, DOG, CAT, COW, SHEEP);
   EXPECT_EQ(static_cast<int>(__hidden_enum_Animals::DOG), 0);
   EXPECT_EQ(static_cast<int>(__hidden_enum_Animals::CAT), 1);
   EXPECT_EQ(static_cast<int>(__hidden_enum_Animals::COW), 2);
   EXPECT_EQ(static_cast<int>(__hidden_enum_Animals::SHEEP), 3);
}
