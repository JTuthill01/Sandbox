#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/ExplosiveProps/ExplosivePropsBase.h"
#include "ExplosiveJerryCanGreen.generated.h"

UCLASS()
class SANDBOX_API AExplosiveJerryCanGreen: public AExplosivePropsBase
{
	GENERATED_BODY()

public:
	AExplosiveJerryCanGreen();

protected:
	virtual void BeginPlay() override;

	virtual void Dead() override;
};
