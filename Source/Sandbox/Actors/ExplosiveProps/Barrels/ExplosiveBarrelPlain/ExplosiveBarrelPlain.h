#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/ExplosiveProps/ExplosivePropsBase.h"
#include "ExplosiveBarrelPlain.generated.h"

UCLASS()
class SANDBOX_API AExplosiveBarrelPlain : public AExplosivePropsBase
{
	GENERATED_BODY()
	
public:
	AExplosiveBarrelPlain();

protected:
	virtual void BeginPlay() override;

	virtual void Dead() override;
};
