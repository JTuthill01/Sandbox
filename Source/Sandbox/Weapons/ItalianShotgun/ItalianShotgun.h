#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "ItalianShotgun.generated.h"

UCLASS()
class SANDBOX_API AItalianShotgun : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AItalianShotgun();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Sounds)
	class USoundBase* ShotgunPump;

protected:
	void WeaponFire(EFireType FireType) override;

	void ShotgunReload() override;

	void BeginPlay() override;

	virtual void ShotgunReloadStart() override;

	virtual void ShotgunReloadLoop() override;

	virtual void ShotgunReloadEnd() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TArray<class UAnimMontage*> ItalianReloadMonatge;
};
