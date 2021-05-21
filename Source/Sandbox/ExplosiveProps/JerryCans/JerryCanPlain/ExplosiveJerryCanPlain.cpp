#include "ExplosiveJerryCanPlain.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"

AExplosiveJerryCanPlain::AExplosiveJerryCanPlain() = default;

void AExplosiveJerryCanPlain::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PropData = Instance->PlainJerryCanData();
}

void AExplosiveJerryCanPlain::Dead()
{
	Super::Dead();

	Destroy();
}
