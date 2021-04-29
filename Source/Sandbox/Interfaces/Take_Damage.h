#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Sandbox/Structs/STR_AmmoData.h"
#include "Take_Damage.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTake_Damage : public UInterface
{
	GENERATED_BODY()
};

class SANDBOX_API ITake_Damage
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Take_Damage(FAmmoData Ammo_Data, float CriticalHitModifer, FHitResult HitResult);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayerTakeDamage(int Damage);
};
