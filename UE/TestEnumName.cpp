#include <Misc/AutomationTest.h>

#include "EnumName/NameOf.h"

namespace
{
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
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTestEnumName, "EnumName.Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FTestEnumName::RunTest(const FString& Parameters)
{
    uint64 Count = GFrameCounter;
    using namespace cppnameof;
    const TCHAR* E0_EXPECTED[] = {TEXT("`anonymous-namespace'::Enum0_0"), TEXT("`anonymous-namespace'::Enum0_1"), TEXT("`anonymous-namespace'::Enum0_2"), TEXT("`anonymous-namespace'::Enum0_3")};
    int32 count = 0;
    for (int32_t i = 0; i <= 5; ++i) {
        auto&& name = NAMEOF_ENUM_TCHAR(static_cast<Enum0>(i));
        if (TEXT('\0')==name[0]) {
            continue;
        }
        UE_LOG(LogTemp, Display, TEXT("[%lld] %s"), Count, name);
        UTEST_EQUAL(TEXT("Enum"), name,  E0_EXPECTED[count]);
        ++count;
    }

    const TCHAR* E1_EXPECTED[] = {TEXT("`anonymous-namespace'::Enum1::E0"), TEXT("`anonymous-namespace'::Enum1::E1")};
    count = 0;
    for (int32_t i = static_cast<int32_t>(Enum1::E0); i <= static_cast<int32_t>(Enum1::E1); ++i) {
        auto&& name = NAMEOF_ENUM_TCHAR<Enum1, static_cast<int32_t>(Enum1::E0), static_cast<int32_t>(Enum1::E1)>(static_cast<Enum1>(i));
        if (TEXT('\0')==name[0]) {
            continue;
        }
        UE_LOG(LogTemp, Display, TEXT("[%lld] %s"), Count, name);
        UTEST_EQUAL(TEXT("Enum"), name,  E1_EXPECTED[count]);
        ++count;
    }

    return true;
}

