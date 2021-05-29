#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "NavySMG.generated.h"

UCLASS()
class SANDBOX_API ANavySMG : public AWeaponBase
{
	GENERATED_BODY()

public:
	ANavySMG();
	
protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;
};
