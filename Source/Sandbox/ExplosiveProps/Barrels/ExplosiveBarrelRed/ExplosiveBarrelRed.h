#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/ExplosiveProps/ExplosivePropsBase.h"
#include "ExplosiveBarrelRed.generated.h"

UCLASS()
class SANDBOX_API AExplosiveBarrelRed : public AExplosivePropsBase
{
	GENERATED_BODY()

public:
	AExplosiveBarrelRed();

protected:
	virtual void BeginPlay() override;

	virtual void Dead() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Impulse);
	float ImpulseForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Impulse);
	float ImpulseRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Impulse);
	float RemoveTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VFX)
	class UNiagaraSystem* SecondExplosionFX;

private:
	FTimerHandle RemoveBarrelTimer;
};
