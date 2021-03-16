#include "StopFireAnimNotify.h"
#include "Sandbox/Character/PlayerCharacter.h"

void UStopFireAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());

		if (Character != NULL)
		{
			Character->SetCanFire(false);
		}
	}
}
