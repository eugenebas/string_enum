#include <gtest/gtest.h>
#include "internal/names.hpp"

#define QUOTE(EXP) #EXP
#define QUOTE_MACRO(MACRO) QUOTE(MACRO)

TEST(names_tests, __STR_ENUM__BASE_STRING_ENUM_NAME) {
    EXPECT_STREQ(QUOTE_MACRO(__STR_ENUM__BASE_STRING_ENUM_NAME(ABC)), "__base_class_ABC");
    EXPECT_STREQ(QUOTE_MACRO(__STR_ENUM__BASE_STRING_ENUM_NAME(VeryGoodEnumName)), "__base_class_VeryGoodEnumName");
    EXPECT_STREQ(QUOTE_MACRO(__STR_ENUM__BASE_STRING_ENUM_NAME(FooBar)), "__base_class_FooBar");
}

TEST(names_tests, __STR_ENUM__INNER_ENUM_CLASS_NAME) {
    EXPECT_STREQ(QUOTE_MACRO(__STR_ENUM__INNER_ENUM_CLASS_NAME(JohnDoe)), "__hidden_enum_JohnDoe");
    EXPECT_STREQ(QUOTE_MACRO(__STR_ENUM__INNER_ENUM_CLASS_NAME(VeryGoodEnumName)), "__hidden_enum_VeryGoodEnumName");
    EXPECT_STREQ(QUOTE_MACRO(__STR_ENUM__INNER_ENUM_CLASS_NAME(FooBar)), "__hidden_enum_FooBar");
}

TEST(names_tests, __STR_ENUM__INNER_ARRAY_NAME) {
    EXPECT_STREQ(QUOTE_MACRO(__STR_ENUM__INNER_ARRAY_NAME(MysteriousArray)), "__hidden_array_MysteriousArray");
    EXPECT_STREQ(QUOTE_MACRO(__STR_ENUM__INNER_ARRAY_NAME(VeryGoodEnumName)), "__hidden_array_VeryGoodEnumName");
    EXPECT_STREQ(QUOTE_MACRO(__STR_ENUM__INNER_ARRAY_NAME(FooBar)), "__hidden_array_FooBar");
}
