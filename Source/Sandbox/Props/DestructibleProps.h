#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sandbox/Interfaces/Take_Damage.h"
#include "DestructibleProps.generated.h"

UCLASS()
class SANDBOX_API ADestructibleProps : public AActor, public ITake_Damage
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleProps();

	virtual void Take_Melee_Damage_Implementation(int32 DamageToTake, FHitResult HitResult) override;

public:
	UFUNCTION()
	void Destroy(float Damage, FVector HitLocation, FVector ImpulseDirection, float Impulse);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
	class UDestructibleComponent* DestructibleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Bool)
	bool bIsTriggerEnabled;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Bool)
	bool bIsDestroyed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health)
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health)
	float Maxhealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Damage)
	float DefaultDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Damage)
	float DefaultImpulse;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
