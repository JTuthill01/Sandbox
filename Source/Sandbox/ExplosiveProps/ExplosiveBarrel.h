#pragma once

#include "CoreMinimal.h"
#include "ExplosivePropsBase.h"
#include "ExplosiveBarrel.generated.h"

UCLASS()
class SANDBOX_API AExplosiveBarrel : public AExplosivePropsBase
{
	GENERATED_BODY()

public:
	AExplosiveBarrel();

	virtual void SetDamageRadius(float Radius) override { Radius = DamageRadius; };

protected:
	virtual void BeginPlay() override;

	virtual void OnPropHit_Implementation(int32 DamageToTake, FHitResult HitResult) override;

	virtual void SetDamage(int32 Damage, FHitResult HitResult, int32& DamageToApply) override;

	virtual void UpdateHealth(int32 Damage, bool& IsDead) override;
};
