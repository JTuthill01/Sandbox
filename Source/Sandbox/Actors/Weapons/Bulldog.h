#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Bulldog.generated.h"

UCLASS()
class SANDBOX_API ABulldog : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	ABulldog();

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<class UAnimMontage*> BulldogMonatge;
};
