#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STR_AmmoData.generated.h"

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float CriticalHit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float DamageRadius;
};


UCLASS()
class SANDBOX_API ASTR_AmmoData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTR_AmmoData();
};
