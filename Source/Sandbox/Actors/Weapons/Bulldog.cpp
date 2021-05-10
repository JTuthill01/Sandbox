#include "Bulldog.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox/Instances/SandboxGameInstance.h"

ABulldog::ABulldog() = default;

void ABulldog::WeaponFire(EFireType FireType)
{
	Super::WeaponFire(fireType);

	FireTransform = WeaponMesh->GetSocketTransform("Fire_FX_Slot");

	FireTransform.GetRotation() = FireQuat;

	WeaponFireAnim = WeaponMesh->GetAnimInstance();

	if (WeaponFireAnim)
	{
		WeaponFireAnim->Montage_Play(WeaponFireMontage);

		UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh);

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FireFX, FireTransform.GetTranslation(), FireQuat.Rotator());
	}
}

void ABulldog::WeaponReload()
{
	Super::WeaponReload();

	WeaponReloadAnim = WeaponMesh->GetAnimInstance();

	int32 LoopAmount = FullMag - CurrentAmmo;

	if (WeaponReloadAnim)
	{
		WeaponReloadAnim->Montage_Play(BulldogMonatge[EShotgunReloadIndex::Start]);

		for (size_t i = 0; i < LoopAmount; ++i)
		{
			WeaponReloadAnim->Montage_Play(BulldogMonatge[EShotgunReloadIndex::Loop]);
		}

		WeaponReloadAnim->Montage_Play(BulldogMonatge[EShotgunReloadIndex::End]);
	}
}

void ABulldog::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	AmmoData = Instance->BulldogData();
}
