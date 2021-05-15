#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarHammer.generated.h"

UCLASS()
class SANDBOX_API AWarHammer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarHammer();

	FORCEINLINE FName GetHammerSocketName() const { return SocketName; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnImpact(FHitResult HitResult);

	UFUNCTION(BlueprintCallable)
	void AddHit(FHitResult HitResult);

	UFUNCTION(BlueprintCallable)
	void OnHammerStrike(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	void OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void SetDecalLocation(FHitResult Result);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USkeletalMeshComponent* HammerMesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UCapsuleComponent* CollisionCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterialInterface* FleshDecalMaterial;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class AAICharacter* AICharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* FleshFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* FleshSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName SocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator DecalRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DecalSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DecalLifeSpan;
};
