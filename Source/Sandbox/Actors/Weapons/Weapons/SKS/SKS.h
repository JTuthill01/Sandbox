#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "SKS.generated.h"

UCLASS()
class SANDBOX_API ASKS : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	ASKS();

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* Sight;
};
