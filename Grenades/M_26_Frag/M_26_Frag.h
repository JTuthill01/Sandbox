#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Grenades/GrenadeBase.h"
#include "M_26_Frag.generated.h"

UCLASS()
class SANDBOX_API AM_26_Frag : public AGrenadeBase
{
	GENERATED_BODY()
	
public:
	AM_26_Frag();

	virtual void OnReleased(FVector ForwardVector) override;

	virtual void Explode() override;
};
