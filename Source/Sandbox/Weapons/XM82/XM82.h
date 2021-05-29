#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "XM82.generated.h"

UCLASS()
class SANDBOX_API AXM82 : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AXM82();

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;
};
