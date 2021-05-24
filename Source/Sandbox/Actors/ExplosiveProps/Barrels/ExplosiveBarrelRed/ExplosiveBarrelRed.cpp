#include "ExplosiveBarrelRed.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AExplosiveBarrelRed::AExplosiveBarrelRed() = default;

void AExplosiveBarrelRed::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PropData = Instance->RedBarrelData();
}

void AExplosiveBarrelRed::Dead()
{
	Super::Dead();

	FVector TempVector = ExplosiveProp->GetSocketLocation(PropSocketName);

	float TempFloat = ImpulseForce * ExplosiveProp->GetMass();

	FVector NewVector(0, 0, TempFloat);

	ExplosiveProp->AddImpulse(NewVector);

	FTimerDelegate Delegate;
	Delegate.BindLambda([this] { Destroy(); });

	GetWorld()->GetTimerManager().SetTimer(RemoveBarrelTimer, Delegate, RemoveTime, false);
}

