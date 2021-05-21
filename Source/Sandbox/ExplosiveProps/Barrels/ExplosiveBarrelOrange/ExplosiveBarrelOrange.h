#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/ExplosiveProps/ExplosivePropsBase.h"
#include "ExplosiveBarrelOrange.generated.h"

UCLASS()
class SANDBOX_API AExplosiveBarrelOrange : public AExplosivePropsBase
{
	GENERATED_BODY()
	
public:
	AExplosiveBarrelOrange();

protected:
	virtual void BeginPlay() override;

	virtual void Dead() override;
};
