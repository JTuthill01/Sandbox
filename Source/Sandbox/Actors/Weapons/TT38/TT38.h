#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "TT38.generated.h"

UCLASS()
class SANDBOX_API ATT38 : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	ATT38();

protected:

	void WeaponReload() override;

	void WeaponFire(EFireType FireType) override;

	void BeginPlay() override;
};
