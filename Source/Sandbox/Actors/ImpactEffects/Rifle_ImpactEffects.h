#pragma once

#include "CoreMinimal.h"
#include "ImpactEffects.h"
#include "Rifle_ImpactEffects.generated.h"

UCLASS()
class SANDBOX_API ARifle_ImpactEffects : public AImpactEffects
{
	GENERATED_BODY()
	
public:
	ARifle_ImpactEffects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
