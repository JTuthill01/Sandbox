#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "AK74.generated.h"

UCLASS()
class SANDBOX_API AAK74 : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AAK74();

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;
};
