#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/ExplosiveProps/ExplosivePropsBase.h"
#include "ExplosivePropaneGasCylinderPlain.generated.h"

UCLASS()
class SANDBOX_API AExplosivePropaneGasCylinderPlain : public AExplosivePropsBase
{
	GENERATED_BODY()
	
public:
	AExplosivePropaneGasCylinderPlain();

protected:
	virtual void BeginPlay() override;

	virtual void Dead() override;
};
