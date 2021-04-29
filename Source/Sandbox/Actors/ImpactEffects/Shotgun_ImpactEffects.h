#pragma once

#include "CoreMinimal.h"
#include "ImpactEffects.h"
#include "Shotgun_ImpactEffects.generated.h"

UCLASS()
class SANDBOX_API AShotgun_ImpactEffects : public AImpactEffects
{
	GENERATED_BODY()
	
public:
	AShotgun_ImpactEffects();

protected:
	virtual void BeginPlay() override;
};
