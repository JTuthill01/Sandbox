#pragma once

#include "CoreMinimal.h"
#include "SandBox/Actors/ExplosiveProps/ExplosivePropsBase.h"
#include "PropaneCylinderTallYellow.generated.h"

UCLASS()
class SANDBOX_API APropaneCylinderTallYellow : public AExplosivePropsBase
{
	GENERATED_BODY()

public:
	APropaneCylinderTallYellow();
	
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
