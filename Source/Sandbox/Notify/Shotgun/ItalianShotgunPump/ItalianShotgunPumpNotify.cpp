#include "ItalianShotgunPumpNotify.h"
#include "Sandbox/Actors/Weapons/ItalianShotgun/ItalianShotgun.h"
#include "Kismet/GameplayStatics.h"

void UItalianShotgunPumpNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AItalianShotgun* Weapon = Cast<AItalianShotgun>(MeshComp->GetOwner());

		if (Weapon != NULL)
		{
			UGameplayStatics::SpawnSoundAttached(Weapon->ShotgunPump, MeshComp);
		}
	}
}
