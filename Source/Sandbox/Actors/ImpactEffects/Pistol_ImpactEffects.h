#pragma once

#include "CoreMinimal.h"
#include "ImpactEffects.h"
#include "Pistol_ImpactEffects.generated.h"

UCLASS()
class SANDBOX_API APistol_ImpactEffects : public AImpactEffects
{
	GENERATED_BODY()
	
public:
	APistol_ImpactEffects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
