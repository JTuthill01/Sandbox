#include "PropaneCylinderTallYellow.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"

APropaneCylinderTallYellow::APropaneCylinderTallYellow() = default;

void APropaneCylinderTallYellow::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PropData = Instance->PropaneCylinderTallYellowData();
}

void APropaneCylinderTallYellow::Dead()
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
