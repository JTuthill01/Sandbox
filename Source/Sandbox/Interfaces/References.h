#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "References.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UReferences : public UInterface
{
	GENERATED_BODY()
};

class SANDBOX_API IReferences
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	class AImpactEffects* GetImpactRef();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	class AAICharacter* GetAICharacterRef();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	class AProjectileBase* GetProjectileRef();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	class AWeaponBase* GetWeaponRef();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	class AExplosivePropsBase* GetExplosivePropRef();
};
