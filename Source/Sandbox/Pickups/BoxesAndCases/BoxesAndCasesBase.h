#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxesAndCasesBase.generated.h"

class APickupBase;

UCLASS()
class SANDBOX_API ABoxesAndCasesBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxesAndCasesBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddWidget(AActor* OtherActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RemoveWidget(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void InteractBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void InteractEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void RemoveLid();

	UFUNCTION(BlueprintCallable)
	void Open();

	UFUNCTION(BlueprintCallable)
	virtual void SpawnCasePickup();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	class UStaticMeshComponent* Hull;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	class UStaticMeshComponent* Lid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	class UBoxComponent* BoxCollision;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	FVector MeshLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Booleans)
	bool bHasBeenOpened;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Varaibles)
	float TimeToRemove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	int32 PickupIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	int32 CurrentIndex;

protected:
	FTimerHandle RemoveLidTimer;
};
