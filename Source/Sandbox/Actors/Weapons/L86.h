#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "L86.generated.h"

UCLASS()
class SANDBOX_API AL86 : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AL86();

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Sight;
};
