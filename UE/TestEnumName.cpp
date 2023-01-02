#include "TestEnumName.h"
#include "NameOf.h"

ATestEnumName::ATestEnumName()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATestEnumName::BeginPlay()
{
	Super::BeginPlay();
}

void ATestEnumName::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    uint64 Count = GFrameCounter;
    using namespace cppnameof;
    for (int32_t i = 0; i <= 5; ++i) {
        auto&& name = get_enum_name_tchar(static_cast<Enum0>(i));
        if (TEXT('\0')==name[0]) {
            continue;
        }
        UE_LOG(LogTemp, Display, TEXT("[%lld] %s"), Count, name);
    }
    for (int32_t i = static_cast<int32_t>(Enum1::E0); i <= static_cast<int32_t>(Enum1::E1); ++i) {
        auto&& name = get_enum_name_tchar_<Enum1, static_cast<int32_t>(Enum1::E0), static_cast<int32_t>(Enum1::E1)>(static_cast<Enum1>(i));
        if (TEXT('\0')==name[0]) {
            continue;
        }
        UE_LOG(LogTemp, Display, TEXT("[%lld] %s"), Count, name);
    }
}


