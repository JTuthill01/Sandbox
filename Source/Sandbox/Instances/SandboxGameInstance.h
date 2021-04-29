#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Sandbox/Structs/STR_AmmoData.h"
#include "SandboxGameInstance.generated.h"

UCLASS()
class SANDBOX_API USandboxGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USandboxGameInstance();
	
	UFUNCTION()
	FAmmoData AK47Data();

	UFUNCTION()
	FAmmoData AmericanShotgunData();

	UFUNCTION()
	FAmmoData BelgianARData();

	UFUNCTION()
	FAmmoData BulldogData();

	UFUNCTION()
	FAmmoData HandCannonData();

	UFUNCTION()
	FAmmoData L86Data();

	UFUNCTION()
	FAmmoData ShortStrokeARData();

	UFUNCTION()
	FAmmoData SKSData();

	UFUNCTION()
	FAmmoData SMGData();

	UFUNCTION()
	FAmmoData T38Data();

	UFUNCTION()
	FAmmoData XM82Data();

private:
	UPROPERTY()
	FAmmoData AK47AmmoData;

	UPROPERTY()
	FAmmoData AmericanShotgunAmmoData;

	UPROPERTY()
	FAmmoData BelgianARAmmoData;

	UPROPERTY()
	FAmmoData BulldogAmmoData;

	UPROPERTY()
	FAmmoData HandCannonAmmoData;

	UPROPERTY()
	FAmmoData L86AmmoData;

	UPROPERTY()
	FAmmoData ShortStrokeARAmmoData;

	UPROPERTY()
	FAmmoData SKSAmmoData;

	UPROPERTY()
	FAmmoData SMGAmmoData;

	UPROPERTY()
	FAmmoData T38AmmoData;

	UPROPERTY()
	FAmmoData XM82AmmoData;
};
