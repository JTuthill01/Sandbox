#include "ItalianShotgun.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Sandbox/Character/PlayerCharacter.h"

AItalianShotgun::AItalianShotgun() = default;

void AItalianShotgun::WeaponFire(EFireType FireType)
{
	Super::WeaponFire(fireType);

	EjectTransform = WeaponMesh->GetSocketTransform("AmmoEject");

	EjectTransform.GetRotation() = EjectQuat;

	FireTransform = WeaponMesh->GetSocketTransform("Fire_FX_Slot");

	FireTransform.GetRotation() = FireQuat;

	WeaponFireAnim = WeaponMesh->GetAnimInstance();

	if (WeaponFireAnim)
	{
		WeaponFireAnim->Montage_Play(WeaponFireMontage);

		UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh);

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), AmmoEject, EjectTransform.GetTranslation(), EjectQuat.Rotator());

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FireFX, FireTransform.GetTranslation(), FireQuat.Rotator());
	}
}

void AItalianShotgun::ShotgunReload()
{
	Super::ShotgunReload();
}

void AItalianShotgun::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	AmmoData = Instance->ItalianShotgunData();

	WeaponReloadAnim = WeaponMesh->GetAnimInstance();
}

void AItalianShotgun::ShotgunReloadStart()
{
	Super::ShotgunReloadStart();

	WeaponReloadAnim->Montage_Play(ItalianReloadMonatge[EShotgunReloadIndex::Start]);

	PlayerRef->Instance->Montage_Play(PlayerRef->ItalianShotgunReloadMonatge[EShotgunReloadIndex::Start]);
}

void AItalianShotgun::ShotgunReloadLoop()
{
	Super::ShotgunReloadLoop();

	WeaponReloadAnim->Montage_Play(ItalianReloadMonatge[EShotgunReloadIndex::Loop]);

	PlayerRef->Instance->Montage_Play(PlayerRef->ItalianShotgunReloadMonatge[EShotgunReloadIndex::Loop]);

	bIsReloading = true;
}

void AItalianShotgun::ShotgunReloadEnd()
{
	Super::ShotgunReloadEnd();

	WeaponReloadAnim->Montage_Play(ItalianReloadMonatge[EShotgunReloadIndex::End]);

	PlayerRef->Instance->Montage_Play(PlayerRef->ItalianShotgunReloadMonatge[EShotgunReloadIndex::End]);

	bIsReloading = false;
}
