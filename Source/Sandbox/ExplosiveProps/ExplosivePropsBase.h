#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sandbox/Interfaces/OnExplosivePropTakeDamage.h"
#include "Sandbox/Interfaces/Take_Damage.h"
#include "Sandbox/Interfaces/References.h"
#include "Sandbox/Structs/STR_PropData.h"
#include "Sandbox/Enums/Enums.h"
#include "ExplosivePropsBase.generated.h"

UCLASS()
class SANDBOX_API AExplosivePropsBase : public AActor, public IOnExplosivePropTakeDamage, public ITake_Damage, public IReferences
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosivePropsBase();

	virtual AExplosivePropsBase* GetExplosivePropRef_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Struct)
	FPropData PropData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EPropType PropType;

public:
	FORCEINLINE class UStaticMeshComponent* GetPropMesh() { return ExplosiveProp; }
	FORCEINLINE FName GetPropName() { return PropName; }

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
	virtual void Dead();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Name)
	FName PropName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Name)
	FName PropSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int32 CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	bool bShouldDealDamage;
};
