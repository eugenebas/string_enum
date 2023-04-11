#include "string_enum.hpp"
#include <iostream>

STRING_ENUM(my_enum,
            A,
            B,
            C)

int main(int argc, char** argv) {
    std::cout << (int)my_enum::__hidden_enum_my_enum::A << "\t"
              << (int)my_enum::__hidden_enum_my_enum::B << "\t"
              << (int)my_enum::__hidden_enum_my_enum::C << std::endl;
    std::cout << my_enum::__hidden_array_my_enum[0] << "\t"
              << my_enum::__hidden_array_my_enum[1] << "\t"
              << my_enum::__hidden_array_my_enum[2] << "\t" << std::endl;

    std::cout << my_enum(my_enum::__hidden_enum_my_enum::C) << std::endl;

    std::cout << static_cast<const char*>(my_enum::A) << std::endl;

    my_enum m = my_enum::B;
    switch(m) {
        case my_enum::A: {
            std::cout << "this is A case!" << std::endl;
            break;
        }
        case my_enum::B: {
            std::cout << "this is B case!" << std::endl;
            break;
        }
        case my_enum::C: {
            std::cout << "this is C case!" << std::endl;
            break;
        }
        default: {
            std::cout << "WTF?! default case" << std::endl;
        }
    }

    std::cout << (my_enum::A == my_enum::B) << std::endl;
    bool greater = my_enum::__hidden_enum_my_enum::A > my_enum::__hidden_enum_my_enum::B;
    return 0;
}

//#define test_macro(...) __STR_ENUM_COUNT_ARGS(__VA_ARGS__)
//#define wrapper(name, ...) test_macro(__VA_ARGS__)

//int main(int argc, char** argv) {
//    std::cout << wrapper(wrap, A, B, C) << std::endl;
//    return 0;
//}
