#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sandbox/Structs/STR_AmmoData.h"
#include "Sandbox/Interfaces/References.h"
#include "ProjectileBase.generated.h"

UCLASS()
class SANDBOX_API AProjectileBase : public AActor, public IReferences
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

	virtual AProjectileBase* GetProjectileRef_Implementation() override;

	UFUNCTION()
	void SetAmmoData(FAmmoData Data) { AmmoData = Data; }

	UFUNCTION()
	void SetModifier(float Modifier) { CriticalHitModifier = Modifier; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	class APlayerCharacter* PlayerRef;

	UPROPERTY()
	class AAICharacter* AICharacterRef;

	UPROPERTY()
	class AImpactEffects* Effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AImpactEffects> EffectToSpawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USphereComponent* Sphere;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UParticleSystemComponent* TrailFX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsCausingRadiusDamage;

	/*UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AExplosionImpulse> Impulse;*/

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CriticalHitModifier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAmmoData AmmoData;

protected:
	UFUNCTION(BlueprintCallable)
	virtual void ProjectileStop(const FHitResult& HitResult);

	UFUNCTION(BlueprintCallable)
	virtual void ExplodeOnImpact(const FHitResult& HitResult);

	UFUNCTION()
	virtual void Spawn(const FHitResult& HitResult);

	UFUNCTION()
	void DealDamage(const FHitResult& HitResult);

	UFUNCTION()
	void SpawnImpact(const FHitResult& HitResult);
};
