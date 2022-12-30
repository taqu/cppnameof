#include "cppnameof.h"
#include <iostream>

enum Enum0
{
    Enum0_0 = 0,
    Enum0_1 = 2,
    Enum0_2 = 3,
    Enum0_3 = 5,
};

enum class Enum1
{
    E0 = -128,
    E1 = 127,
};

int main(void)
{
    using namespace cppnameof;
    for(int32_t i = 0; i <= 5; ++i) {
        auto&& name = get_enum_name(static_cast<Enum0>(i));
        if(name.length()<=0){
            continue;
        }
        std::cout << name << std::endl;
    }
    for(int32_t i = static_cast<int32_t>(Enum1::E0); i <= static_cast<int32_t>(Enum1::E1); ++i) {
        auto&& name = get_enum_name_<Enum1, static_cast<int32_t>(Enum1::E0), static_cast<int32_t>(Enum1::E1)>(static_cast<Enum1>(i));
        if(name.length()<=0){
            continue;
        }
        std::cout << name << std::endl;
    }
    return 0;
}
