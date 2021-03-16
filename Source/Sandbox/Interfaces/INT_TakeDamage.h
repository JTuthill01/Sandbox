#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "INT_TakeDamage.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UINT_TakeDamage : public UInterface
{
	GENERATED_BODY()
};


class SANDBOX_API IINT_TakeDamage
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void TakeDamage(FAmmoData AmmoData, float Damage, float CriticalHitModifier, FHitResult Hit);
};
