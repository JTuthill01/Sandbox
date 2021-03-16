#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "SMG.generated.h"

UCLASS()
class SANDBOX_API ASMG : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	ASMG();

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;
};
