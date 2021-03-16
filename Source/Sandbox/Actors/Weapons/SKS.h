#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
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
