#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerRef.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerRef : public UInterface
{
	GENERATED_BODY()
};

class SANDBOX_API IPlayerRef
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	class APlayerCharacter* GetPlayerRef();
};
