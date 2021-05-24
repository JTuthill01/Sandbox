#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Grenades/GrenadeBase.h"
#include "MKII_Frag.generated.h"

UCLASS()
class SANDBOX_API AMKII_Frag : public AGrenadeBase
{
	GENERATED_BODY()
	
public:
	AMKII_Frag();

	virtual void OnReleased(FVector ForwardVector) override;

	virtual void Explode() override;
};
