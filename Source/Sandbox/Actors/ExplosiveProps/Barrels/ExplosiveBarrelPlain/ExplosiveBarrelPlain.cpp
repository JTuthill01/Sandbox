#include "ExplosiveBarrelPlain.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"

AExplosiveBarrelPlain::AExplosiveBarrelPlain() = default;

void AExplosiveBarrelPlain::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PropData = Instance->PlainBarrelData();
}

void AExplosiveBarrelPlain::Dead()
{
	Super::Dead();

	Destroy();
}
