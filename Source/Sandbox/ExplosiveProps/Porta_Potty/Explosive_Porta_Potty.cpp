#include "Explosive_Porta_Potty.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

AExplosive_Porta_Potty::AExplosive_Porta_Potty()
{
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(ExplosiveProp);

	FireFXComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire FX Component"));
	FireFXComponent->SetupAttachment(ExplosiveProp);
	FireFXComponent->bAutoActivate = false;

	ExplosiveProp->SetSimulatePhysics(true);
}

void AExplosive_Porta_Potty::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PropData = Instance->PortaPottyData();

	FireTimer = 10.F;
}

void AExplosive_Porta_Potty::Dead()
{
	Super::Dead();

	FVector TempVector = ExplosiveProp->GetSocketLocation(PropSocketName);

	float TempFloat = ImpulseForce * ExplosiveProp->GetMass();

	FVector NewVector(0, 0, TempFloat);

	ExplosiveProp->AddImpulse(NewVector);

	FVector DoorVector = DoorMesh->GetComponentLocation();

	DoorMesh->SetSimulatePhysics(true);

	float DoorFloat = DoorImpulseForce * DoorMesh->GetMass();

	FVector NewDoorVector(DoorFloat, 0, 0);

	DoorMesh->AddImpulse(NewDoorVector);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SecondExplosionFX, TempVector);

	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AExplosive_Porta_Potty::StartFire, FireTimer, false);
}

void AExplosive_Porta_Potty::StartFire()
{
	FireFXComponent->Activate(true);

	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}
