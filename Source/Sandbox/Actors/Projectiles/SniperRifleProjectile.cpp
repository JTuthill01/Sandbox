#include "SniperRifleProjectile.h"
#include "Sandbox/Actors/ImpactEffects/ImpactEffects.h"
#include "Kismet/GameplayStatics.h"

ASniperRifleProjectile::ASniperRifleProjectile() = default;

void ASniperRifleProjectile::BeginPlay()
{
	Super::BeginPlay();

	bIsCausingRadiusDamage = false;
}

