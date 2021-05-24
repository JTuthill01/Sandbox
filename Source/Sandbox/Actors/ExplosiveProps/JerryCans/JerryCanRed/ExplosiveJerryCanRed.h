#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/ExplosiveProps/ExplosivePropsBase.h"
#include "ExplosiveJerryCanRed.generated.h"

UCLASS()
class SANDBOX_API AExplosiveJerryCanRed : public AExplosivePropsBase
{
	GENERATED_BODY()

public:
	AExplosiveJerryCanRed();

protected:
	virtual void BeginPlay() override;

	virtual void Dead() override;
};
