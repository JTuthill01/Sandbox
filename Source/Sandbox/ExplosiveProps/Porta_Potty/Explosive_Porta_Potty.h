#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/ExplosiveProps/ExplosivePropsBase.h"
#include "Explosive_Porta_Potty.generated.h"

UCLASS()
class SANDBOX_API AExplosive_Porta_Potty : public AExplosivePropsBase
{
	GENERATED_BODY()
	
public:
	AExplosive_Porta_Potty();

protected:
	virtual void BeginPlay() override;

	virtual void Dead() override;

protected:
	UFUNCTION()
	void StartFire();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Door);
	class UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Impulse);
	float ImpulseForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Impulse);
	float DoorImpulseForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Impulse);
	float ImpulseRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle);
	float FireTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
	class UParticleSystem* FireFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
	class UParticleSystemComponent* FireFXComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VFX)
	class UNiagaraSystem* SecondExplosionFX;

private:
	FTimerHandle FireTimerHandle;
};
