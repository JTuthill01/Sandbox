#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Grenades/GrenadeBase.h"
#include "ToxicGrenade.generated.h"

UCLASS()
class SANDBOX_API AToxicGrenade : public AGrenadeBase
{
	GENERATED_BODY()
	
public:
	AToxicGrenade();

	virtual void OnReleased(FVector ForwardVector) override;

	virtual void Explode() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Emitter)
	class UParticleSystem* ToxicEmitter;
};
