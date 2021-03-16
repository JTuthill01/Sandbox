#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "AmericanShotgun.generated.h"

UCLASS()
class SANDBOX_API AAmericanShotgun : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AAmericanShotgun();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Sounds)
	class USoundBase* ShotgunPump;

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;
};
