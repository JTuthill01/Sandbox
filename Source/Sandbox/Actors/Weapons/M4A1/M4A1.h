#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "M4A1.generated.h"

UCLASS()
class SANDBOX_API AM4A1 : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AM4A1();

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;
};
