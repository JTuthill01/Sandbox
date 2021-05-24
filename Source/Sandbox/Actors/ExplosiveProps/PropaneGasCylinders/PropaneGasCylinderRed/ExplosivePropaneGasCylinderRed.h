#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/ExplosiveProps/ExplosivePropsBase.h"
#include "ExplosivePropaneGasCylinderRed.generated.h"

UCLASS()
class SANDBOX_API AExplosivePropaneGasCylinderRed : public AExplosivePropsBase
{
	GENERATED_BODY()

public:
	AExplosivePropaneGasCylinderRed();

protected:
	virtual void BeginPlay() override;

	virtual void Dead() override;
};
