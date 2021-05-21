#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "MicroSMG.generated.h"

UCLASS()
class SANDBOX_API AMicroSMG : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AMicroSMG();

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;
};
