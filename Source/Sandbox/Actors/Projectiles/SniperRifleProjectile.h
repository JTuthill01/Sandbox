#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "SniperRifleProjectile.generated.h"

UCLASS()
class SANDBOX_API ASniperRifleProjectile : public AProjectileBase
{
	GENERATED_BODY()
	
public:
	ASniperRifleProjectile();

protected:
	virtual void BeginPlay() override;
};
