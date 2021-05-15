#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "BelgianAR.generated.h"

UCLASS()
class SANDBOX_API ABelgianAR : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	ABelgianAR();

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Sight;
};
