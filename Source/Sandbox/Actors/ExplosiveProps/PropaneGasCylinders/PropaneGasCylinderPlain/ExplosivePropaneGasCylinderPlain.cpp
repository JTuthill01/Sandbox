#include "ExplosivePropaneGasCylinderPlain.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"

AExplosivePropaneGasCylinderPlain::AExplosivePropaneGasCylinderPlain() = default;

void AExplosivePropaneGasCylinderPlain::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PropData = Instance->PropaneGasCylinderPlainData();
}

void AExplosivePropaneGasCylinderPlain::Dead()
{
	Super::Dead();

	Destroy();
}
