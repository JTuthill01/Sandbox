#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnimatedCases.generated.h"

class APickupBase;

UCLASS()
class SANDBOX_API AAnimatedCases : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimatedCases();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddWidget(AActor* OtherActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RemoveWidget(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void Open();

	UFUNCTION(BlueprintCallable)
	void InteractBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void InteractEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void SpawnCasePickups();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	class USkeletalMeshComponent* CaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	class UBoxComponent* BoxCollision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Animation)
	class UAnimationAsset* CaseOpenAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	int32 NumOfPickupsToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	APickupBase* BasePickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	TArray<TSubclassOf<APickupBase>> SpawnArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	TArray<FName> SocketNameArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	FRotator SpawnRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	int32 PickupIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	int32 CurrentIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	bool bHasBeenOpened;
};
