#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "SVD.generated.h"

UCLASS()
class SANDBOX_API ASVD : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	ASVD();

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;
};
