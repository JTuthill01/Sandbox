#include "ExplosiveJerryCanGreen.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"

AExplosiveJerryCanGreen::AExplosiveJerryCanGreen() = default;

void AExplosiveJerryCanGreen::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PropData = Instance->GreenJerryCanData();
}

void AExplosiveJerryCanGreen::Dead()
{
	Super::Dead();

	Destroy();
}
