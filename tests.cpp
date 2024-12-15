#include <gtest/gtest.h>
#include "string_enum.hpp"

STRING_ENUM(Color,
    Red,
    Green,
    Blue
);

TEST(string_enum, selfComparison) {
    EXPECT_EQ(Color::Red,   Color::Red);
    EXPECT_EQ(Color::Green, Color::Green);
    EXPECT_EQ(Color::Blue,  Color::Blue);

    EXPECT_NE(Color::Red, Color::Green);
    EXPECT_NE(Color::Red, Color::Blue);
    EXPECT_NE(Color::Green, Color::Blue);

    EXPECT_GT(Color::Green, Color::Red);
    EXPECT_GT(Color::Blue,  Color::Red);
    EXPECT_GT(Color::Blue,  Color::Green);

    EXPECT_LT(Color::Red,   Color::Green);
    EXPECT_LT(Color::Red,   Color::Blue);
    EXPECT_LT(Color::Green, Color::Blue);
}

TEST(string_enum, constructionFromInt) {
    EXPECT_EQ(Color::Red,   Color(0));
    EXPECT_EQ(Color::Green, Color(1));
    EXPECT_EQ(Color::Blue,  Color(2));
}

TEST(string_enum, integerComparison) {
    EXPECT_EQ(Color::Red,   0);
    EXPECT_EQ(Color::Green, 1);
    EXPECT_EQ(Color::Blue,  2);

    EXPECT_GT(1,  Color::Red);
    EXPECT_GT(Color::Red, -1);
    EXPECT_LT(-1, Color::Red);
    EXPECT_LT(Color::Red, 1);

    EXPECT_GT(2, Color::Green);
    EXPECT_GT(Color::Green, 0);
    EXPECT_LT(0, Color::Green);
    EXPECT_LT(Color::Green, 2);

    EXPECT_GT(3, Color::Blue);
    EXPECT_GT(Color::Blue, 1);
    EXPECT_LT(1, Color::Blue);
    EXPECT_LT(Color::Blue, 3);
}

TEST(string_enum, cstringComparison) {
    EXPECT_STREQ(static_cast<const char*>(Color::Red),   "Red");
    EXPECT_STREQ(static_cast<const char*>(Color::Green), "Green");
    EXPECT_STREQ(static_cast<const char*>(Color::Blue),  "Blue");
}

TEST(string_enum, constructionFromIntExceedingRange) {
    EXPECT_THROW(Color(3), std::invalid_argument);
    EXPECT_THROW(Color(-1), std::invalid_argument);
}

TEST(string_enum, switchExpressionSupport) {
    switch(Color(2)) {
        case Color::Red: FAIL();
        case Color::Green: FAIL();
        case Color::Blue: {
            SUCCEED();
            break;
        }
        default: FAIL();
    }
}

TEST(count_args, count_args) {
    EXPECT_EQ(__STR_ENUM__COUNT_ARGS(A, B, C), 3);
    EXPECT_EQ(__STR_ENUM__COUNT_ARGS(A), 1);
    EXPECT_EQ(__STR_ENUM__COUNT_ARGS(A, B, C, D, E, F, G), 7);
}
