#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
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

	void ShotgunReload() override;

	void BeginPlay() override;

	virtual void ShotgunReloadStart() override;

	virtual void ShotgunReloadLoop() override;

	virtual void ShotgunReloadEnd() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TArray<class UAnimMontage*> AmericanReloadMonatge;
};
