#include <gtest/gtest.h>
#include "internal/count_args.hpp"

TEST(count_args, count_args) {
    EXPECT_EQ(__STR_ENUM__COUNT_ARGS(A, B, C), 3);
    EXPECT_EQ(__STR_ENUM__COUNT_ARGS(A), 1);
    EXPECT_EQ(__STR_ENUM__COUNT_ARGS(A, B, C, D, E, F, G), 7);
}
