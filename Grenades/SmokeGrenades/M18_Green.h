#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Grenades/GrenadeBase.h"
#include "M18_Green.generated.h"

UCLASS()
class SANDBOX_API AM18_Green : public AGrenadeBase
{
	GENERATED_BODY()
	
public:
	AM18_Green();

	virtual void OnReleased(FVector ForwardVector) override;

	virtual void Explode() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Emitter)
	class UParticleSystem* SmokeEmitter;

private:
	FTimerHandle DestroyTimerHandle;
};
