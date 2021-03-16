#include "StartFireAnimNotify.h"
#include "Sandbox/Character/PlayerCharacter.h"

void UStartFireAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());

		if (Character != NULL)
		{
			Character->SetCanFire(true);
		}
	}
}
