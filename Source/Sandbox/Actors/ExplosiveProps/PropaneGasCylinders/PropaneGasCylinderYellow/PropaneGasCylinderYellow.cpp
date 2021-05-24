#include "PropaneGasCylinderYellow.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"

APropaneGasCylinderYellow::APropaneGasCylinderYellow() = default;

void APropaneGasCylinderYellow::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PropData = Instance->PropaneGasCylinderYellowData();
}

void APropaneGasCylinderYellow::Dead()
{
	Super::Dead();

	Destroy();
}
