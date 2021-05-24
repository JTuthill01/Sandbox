#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrenadeBase.generated.h"

UCLASS()
class SANDBOX_API AGrenadeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenadeBase();

	FORCEINLINE FName GetGrenadeSocketName() { return GrenadeSocketName; }

public:
	virtual void OnReleased(FVector ForwardVector);

	virtual void Explode();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	USceneComponent* SceneRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* GrenadeMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Socket)
	FName GrenadeSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sphere)
	class USphereComponent* DamageSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VFX)
	class UNiagaraSystem* ExplosionFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	class USoundBase* ExplosiveSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Fuse)
	float FuseLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Impulse)
	float ImpulseForce;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Smoke)
	float SmokeRemovalTime;

private:
	FTimerHandle TExplodeHandle;
};
