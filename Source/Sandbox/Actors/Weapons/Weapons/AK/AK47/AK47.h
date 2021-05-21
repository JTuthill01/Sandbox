#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "AK47.generated.h"

UCLASS()
class SANDBOX_API AAK47 : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AAK47();

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;
};
