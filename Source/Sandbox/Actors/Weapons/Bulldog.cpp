#include "Bulldog.h"
#include "Kismet/GameplayStatics.h"

ABulldog::ABulldog() = default;

void ABulldog::WeaponFire(EFireType FireType)
{
	Super::WeaponFire(fireType);

	if (WeaponFireAnim)
	{
		WeaponFireAnim->Montage_Play(WeaponFireMontage);

		UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh);
	}
}

void ABulldog::WeaponReload()
{
	Super::WeaponReload();

	WeaponReloadAnim = WeaponMesh->GetAnimInstance();

	if (WeaponReloadAnim)
	{
		WeaponReloadAnim->Montage_Play(WeaponReloadMontage);
	}
}

void ABulldog::BeginPlay()
{
	Super::BeginPlay();
}
