#include "PlayNextNotify.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "Sandbox/Interfaces/References.h"

void UPlayNextNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AWeaponBase* Weapon = Cast<AWeaponBase>(MeshComp->GetOwner());

		if (IsValid(Weapon))
		{
			if (Weapon->GetCurrentAmmo() < Weapon->GetFullMag())
			{
				Weapon->ShotgunReloadLoop();
			}

			else if (Weapon->GetCurrentAmmo() == Weapon->GetFullMag())
			{
				Weapon->ShotgunReloadEnd();
			}
		}
	}
}
