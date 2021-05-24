#include "MKII_Frag.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Sandbox/AI/AICharacter.h"

AMKII_Frag::AMKII_Frag() = default;

void AMKII_Frag::OnReleased(FVector ForwardVector)
{
	Super::OnReleased(ForwardVector);

	ForwardVector *= ImpulseForce;
}

void AMKII_Frag::Explode()
{
	Super::Explode();

	FVector TempVector = GrenadeMesh->GetComponentLocation();

	FRotator TempRotator = GrenadeMesh->GetComponentRotation();

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionFX, TempVector, TempRotator);

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
