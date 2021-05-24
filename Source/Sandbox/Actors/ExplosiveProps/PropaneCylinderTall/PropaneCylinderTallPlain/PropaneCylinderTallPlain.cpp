#include "PropaneCylinderTallPlain.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"

APropaneCylinderTallPlain::APropaneCylinderTallPlain() = default;

void APropaneCylinderTallPlain::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PropData = Instance->PropaneCylinderTallPlainData();
}

void APropaneCylinderTallPlain::Dead()
{
	Super::Dead();

	FVector TempVector = ExplosiveProp->GetSocketLocation(PropSocketName);

	float TempFloat = ImpulseForce * ExplosiveProp->GetMass();

	FVector NewVector(0, 0, TempFloat);

	ExplosiveProp->AddImpulse(NewVector);

	FTimerDelegate Delegate;
	Delegate.BindLambda([this] { Destroy(); });

	GetWorld()->GetTimerManager().SetTimer(RemoveCylinderTimer, Delegate, RemoveTime, false);
}
