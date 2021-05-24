#include "ReloadEndAnimNotify.h"
#include "Sandbox/Character/PlayerCharacter.h"

void UReloadEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner());

		if (Character != NULL)
		{
			Character->SetIsReloading(false);

			Character->SetCanFire(true);
		}
	}
}
