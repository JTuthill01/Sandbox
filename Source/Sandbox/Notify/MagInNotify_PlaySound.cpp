#include "MagInNotify_PlaySound.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "Kismet/GameplayStatics.h"

void UMagInNotify_PlaySound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AWeaponBase* Weapon = Cast<AWeaponBase>(MeshComp->GetOwner());

		if (Weapon != NULL)
		{
			UGameplayStatics::SpawnSoundAttached(Weapon->MagInSound, MeshComp);
		}
	}
}
