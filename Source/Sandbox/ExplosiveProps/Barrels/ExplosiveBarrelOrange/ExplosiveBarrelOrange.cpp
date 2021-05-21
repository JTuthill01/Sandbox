#include "ExplosiveBarrelOrange.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"

AExplosiveBarrelOrange::AExplosiveBarrelOrange() = default;

void AExplosiveBarrelOrange::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PropData = Instance->OrangeBarrelData();
}

void AExplosiveBarrelOrange::Dead()
{
	Super::Dead();

	Destroy();
}
