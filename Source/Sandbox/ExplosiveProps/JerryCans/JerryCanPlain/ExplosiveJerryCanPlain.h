#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/ExplosiveProps/ExplosivePropsBase.h"
#include "ExplosiveJerryCanPlain.generated.h"

UCLASS()
class SANDBOX_API AExplosiveJerryCanPlain : public AExplosivePropsBase
{
	GENERATED_BODY()
	
public:
	AExplosiveJerryCanPlain();

protected:
	virtual void BeginPlay() override;

	virtual void Dead() override;
};
