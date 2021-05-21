#include "ExplosiveJerryCanRed.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"

AExplosiveJerryCanRed::AExplosiveJerryCanRed() = default;

void AExplosiveJerryCanRed::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PropData = Instance->RedJerryCanData();
}

void AExplosiveJerryCanRed::Dead()
{
	Super::Dead();

	Destroy();
}
