#include "GrenadeReleasedAnimNotify.h"
#include "Sandbox/Character/PlayerCharacter.h"

void UGrenadeReleasedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner());

		if (IsValid(Player))
		{
			Player->OnGrenadeReleased();
		}
	}
}
