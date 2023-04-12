#ifndef __STRING_ENUM_HPP__
#define __STRING_ENUM_HPP__

#include <string>
#include <type_traits>
#include <compare>

#include "names.hpp"
#include "count_args.hpp"
#include "generate_strings.hpp"
#include "generate_constants.hpp"
#include <array>


#define __STR_ENUM__STRING_ARRAY(enum_name, ...)\
    constexpr std::array<const char*, __STR_ENUM__COUNT_ARGS(__VA_ARGS__) > __STR_ENUM__INNER_ARRAY_NAME(enum_name) {\
        __STR_ENUM__GENERATE_STRINGS(__VA_ARGS__)\
    };


#define __STR_ENUM__INNER_ENUM(enum_name, ...) enum class __STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name) {__VA_ARGS__};

#define STRING_ENUM(enum_name, ...) \
struct __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name) { \
    __STR_ENUM__INNER_ENUM(enum_name, __VA_ARGS__)\
    static __STR_ENUM__STRING_ARRAY(enum_name, __VA_ARGS__)\
    \
    constexpr __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)(__STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name) value): mValue(value){}\
    constexpr __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)(const __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)& other) = default;\
    \
    __STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name) mValue;\
    public: \
    constexpr operator const char* () const { \
        return __STR_ENUM__INNER_ARRAY_NAME(enum_name)[static_cast<std::underlying_type<__STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name)>::type>(mValue)]; \
    } \
    constexpr operator __STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name) () const { \
        return mValue; \
    } \
    auto operator<=>(const __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)& other) const = default; \
};\
struct enum_name : public __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name) { \
    enum_name(__STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name) value) : __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)(value) {} \
    enum_name(const __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)& other) : __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)(other) {} \
    __STR_ENUM__GENERATE_CONSTANTS(enum_name, __VA_ARGS__) \
};

#endif // __STRING_ENUM_HPP__
