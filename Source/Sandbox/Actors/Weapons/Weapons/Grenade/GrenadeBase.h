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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	class UCapsuleComponent* CapsuleCollision;
};
