#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "ShortStrokeAR.generated.h"

UCLASS()
class SANDBOX_API AShortStrokeAR : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AShortStrokeAR();

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Sight;
};
