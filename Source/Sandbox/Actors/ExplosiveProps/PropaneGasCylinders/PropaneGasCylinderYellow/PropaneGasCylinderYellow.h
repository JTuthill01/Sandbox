#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/ExplosiveProps/ExplosivePropsBase.h"
#include "PropaneGasCylinderYellow.generated.h"

UCLASS()
class SANDBOX_API APropaneGasCylinderYellow : public AExplosivePropsBase
{
	GENERATED_BODY()
	
public:
	APropaneGasCylinderYellow();

protected:
	virtual void BeginPlay() override;

	virtual void Dead() override;
};
