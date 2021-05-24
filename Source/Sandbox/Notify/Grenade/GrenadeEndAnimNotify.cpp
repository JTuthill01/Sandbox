#include "GrenadeEndAnimNotify.h"
#include "Sandbox/Character/PlayerCharacter.h"

void UGrenadeEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner());

		if (IsValid(Player))
		{
			Player->GetCurrentWeapon()->SetActorHiddenInGame(false);
		}
	}
}
