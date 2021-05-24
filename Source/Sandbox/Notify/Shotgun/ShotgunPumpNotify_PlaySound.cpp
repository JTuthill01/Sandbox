#include "ShotgunPumpNotify_PlaySound.h"
#include "Sandbox/Actors/Weapons/AmericanShotgun/AmericanShotgun.h"
#include "Kismet/GameplayStatics.h"

void UShotgunPumpNotify_PlaySound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AAmericanShotgun* Weapon = Cast<AAmericanShotgun>(MeshComp->GetOwner());

		if (Weapon != NULL)
		{
			UGameplayStatics::SpawnSoundAttached(Weapon->ShotgunPump, MeshComp);
		}
	}
}
