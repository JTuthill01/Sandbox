#include "ExplosivePropaneGasCylinderRed.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"

AExplosivePropaneGasCylinderRed::AExplosivePropaneGasCylinderRed() = default;

void AExplosivePropaneGasCylinderRed::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PropData = Instance->PropaneGasCylinderRedData();
}

void AExplosivePropaneGasCylinderRed::Dead()
{
	Super::Dead();

	Destroy();
}
