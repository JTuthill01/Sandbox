#include "PropaneCylinderTallRed.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"

APropaneCylinderTallRed::APropaneCylinderTallRed() = default;

void APropaneCylinderTallRed::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PropData = Instance->PropaneCylinderTallRedData();
}

void APropaneCylinderTallRed::Dead()
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
