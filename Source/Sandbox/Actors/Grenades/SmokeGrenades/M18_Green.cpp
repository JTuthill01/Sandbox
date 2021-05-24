#include "M18_Green.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Sandbox/AI/AICharacter.h"
#include "Particles/ParticleSystem.h"

AM18_Green::AM18_Green() = default;

void AM18_Green::OnReleased(FVector ForwardVector)
{
	Super::OnReleased(ForwardVector);

	ForwardVector *= ImpulseForce;
}

void AM18_Green::Explode()
{
	Super::Explode();

	SmokeEmitter->BeginDestroy();

	FTimerDelegate Delegate;
	Delegate.BindLambda([this] { SmokeEmitter->FinishDestroy(); });

	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, Delegate, SmokeRemovalTime, false);

	FVector TempVector = GrenadeMesh->GetComponentLocation();

	FRotator TempRotator = GrenadeMesh->GetComponentRotation();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SmokeEmitter, TempVector, TempRotator);

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosiveSound, TempVector);

	Destroy();
}
