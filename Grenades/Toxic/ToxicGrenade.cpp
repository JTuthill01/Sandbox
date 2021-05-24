#include "ToxicGrenade.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Sandbox/AI/AICharacter.h"


AToxicGrenade::AToxicGrenade() = default;

void AToxicGrenade::OnReleased(FVector ForwardVector)
{
	Super::OnReleased(ForwardVector);

	ForwardVector *= ImpulseForce;
}

void AToxicGrenade::Explode()
{
	Super::Explode();

	FVector TempVector = GrenadeMesh->GetComponentLocation();

	FRotator TempRotator = GrenadeMesh->GetComponentRotation();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ToxicEmitter, TempVector, TempRotator);

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosiveSound, TempVector);

	TArray<AActor*> OutActors;

	DamageSphere->GetOverlappingActors(OutActors);

	for (auto& Actor : OutActors)
	{
		ITake_Damage* iTemp = Cast<ITake_Damage>(Actor);

		if (iTemp != nullptr)
		{
			if (Actor != nullptr)
			{
				if (Actor->GetClass()->ImplementsInterface(UTake_Damage::StaticClass()))
				{
					iTemp->Execute_TakeGernadeDamage(Actor, 20);
				}
			}
		}
	}

	Destroy();
}
