#ifndef __STRING_ENUM_HPP__
#define __STRING_ENUM_HPP__

#include <array>
#include <compare>
#include <stdexcept>
#include <string>
#include <type_traits>

#include "names.hpp"
#include "count_args.hpp"
#include "generate_strings.hpp"
#include "generate_constants.hpp"

#define __STR_ENUM__STRING_ARRAY(enum_name, ...)\
    constexpr std::array<const char*, __STR_ENUM__COUNT_ARGS(__VA_ARGS__) > __STR_ENUM__INNER_ARRAY_NAME(enum_name) {\
        __STR_ENUM__GENERATE_STRINGS(__VA_ARGS__)\
    };


#define __STR_ENUM__INNER_ENUM(enum_name, ...) enum class __STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name) {__VA_ARGS__};

#define STRING_ENUM(enum_name, ...) \
struct __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name) { \
    protected: \
    __STR_ENUM__INNER_ENUM(enum_name, __VA_ARGS__) \
    static __STR_ENUM__STRING_ARRAY(enum_name, __VA_ARGS__) \
    \
    constexpr __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)(const __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)& other) = default; \
    constexpr __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)(const std::underlying_type_t<__STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name)>& value): \
        mValue(static_cast<__STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name)>(value)) { \
        if(value < 0 || value >= __STR_ENUM__INNER_ARRAY_NAME(enum_name).size()) { \
            throw std::invalid_argument("integer value out of enum scope"); \
        } \
    }\
    \
    __STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name) mValue; \
    public: \
    constexpr __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)(__STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name) value): mValue(value){} \
    constexpr operator const char* () const { \
        return __STR_ENUM__INNER_ARRAY_NAME(enum_name)[static_cast<std::underlying_type<__STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name)>::type>(mValue)]; \
    } \
    constexpr operator __STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name) () const { \
        return mValue; \
    } \
    auto operator<=>(const __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)& other) const = default; \
    constexpr bool operator==(const __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)& other) const = default; \
    auto operator<=>(const std::underlying_type_t<__STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name)>& integerValue) const { \
        return static_cast<std::underlying_type_t<__STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name)>>(mValue) <=> integerValue; \
    } \
    constexpr bool operator==(const std::underlying_type_t<__STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name)>& integerValue) const { \
        return static_cast<std::underlying_type_t<__STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name)>>(mValue) == integerValue; \
    } \
};\
\
struct enum_name final : __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name) { \
    enum_name(__STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name) value) : __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)(value) {} \
    enum_name(const __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)& other) : __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)(other) {} \
    enum_name(const std::underlying_type_t<__STR_ENUM__INNER_ENUM_CLASS_NAME(enum_name)>& value) : __STR_ENUM__BASE_STRING_ENUM_NAME(enum_name)(value){} \
    __STR_ENUM__GENERATE_CONSTANTS(enum_name, __VA_ARGS__) \
};

#endif // __STRING_ENUM_HPP__
