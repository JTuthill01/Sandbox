#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sandbox/Interfaces/OnExplosivePropTakeDamage.h"
#include "Sandbox/Interfaces/Take_Damage.h"
#include "Sandbox/Interfaces/References.h"
#include "ExplosivePropsBase.generated.h"

UCLASS()
class SANDBOX_API AExplosivePropsBase : public AActor, public IOnExplosivePropTakeDamage, public ITake_Damage, public IReferences
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosivePropsBase();

	virtual AExplosivePropsBase* GetExplosivePropRef_Implementation() override;

	FORCEINLINE virtual void SetDamageRadius(float Radius) { DamageRadius = Radius; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	float DamageRadius;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPropHit_Implementation(int32 DamageToTake, FHitResult HitResult) override;

protected:
	UFUNCTION(BlueprintCallable)
	virtual void SetDamage(int32 Damage, FHitResult HitResult, int32& DamageToApply);

	UFUNCTION(BlueprintCallable)
	virtual void UpdateHealth(int32 Damage, bool& IsDead);

	UFUNCTION(BlueprintCallable)
	void Dead();

protected:
	UPROPERTY()
	class APlayerCharacter* PlayerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	class UStaticMeshComponent* ExplosiveProp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VFX)
	class UNiagaraSystem* ExplosionFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	class USoundBase* ExplosiveSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int32 CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	bool bShouldDealDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnLocation)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnLocation)
	FRotator Rotation;
};
