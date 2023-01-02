#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include <string>
#include "TestEnumName.generated.h"

UCLASS()
class ENUMNAME_API ATestEnumName : public AActor
{
	GENERATED_BODY()
	
public:	
	ATestEnumName();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
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

};
