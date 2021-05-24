#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OnExplosivePropTakeDamage.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UOnExplosivePropTakeDamage : public UInterface
{
	GENERATED_BODY()
};

class SANDBOX_API IOnExplosivePropTakeDamage
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPropHit(int32 DamageToTake, FHitResult HitResult);
};
