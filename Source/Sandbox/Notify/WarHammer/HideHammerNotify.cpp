#include "HideHammerNotify.h"
#include "Sandbox/Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UHideHammerNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner());

		if (IsValid(Player))
		{
			Player->HideHammer(true);
		}
	}
}
