#pragma once

#include "CoreMinimal.h"
#include "SandBox/Actors/ExplosiveProps/ExplosivePropsBase.h"
#include "PropaneCylinderTallRed.generated.h"

UCLASS()
class SANDBOX_API APropaneCylinderTallRed : public AExplosivePropsBase
{
	GENERATED_BODY()
	
public:
	APropaneCylinderTallRed();

protected:
	virtual void BeginPlay() override;

	virtual void Dead() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Impulse)
	float ImpulseForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Impulse);
	float ImpulseRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Impulse);
	float RemoveTime;

private:
	FTimerHandle RemoveCylinderTimer;
};
