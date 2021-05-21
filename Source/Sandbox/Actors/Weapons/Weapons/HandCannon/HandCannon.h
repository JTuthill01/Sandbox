#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "HandCannon.generated.h"

UCLASS()
class SANDBOX_API AHandCannon : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AHandCannon();

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = VFX)
	class UParticleSystem* EmitterFX;
};
