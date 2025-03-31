#ifndef __STR_ENUM__INNER_STRING_ARRAY_HPP_
#define __STR_ENUM__INNER_STRING_ARRAY_HPP_

#define __STR_ENUM__INNER_STRING_ARRAY(enum_name, ...)\
    constexpr std::array<const char*, __STR_ENUM__COUNT_ARGS(__VA_ARGS__) > __STR_ENUM__INNER_ARRAY_NAME(enum_name) {\
        __STR_ENUM__GENERATE_STRINGS(__VA_ARGS__)\
    };

#endif // __STR_ENUM__INNER_STRING_ARRAY_HPP_
