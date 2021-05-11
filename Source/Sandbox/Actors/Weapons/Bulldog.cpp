#include "Bulldog.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Sandbox/Character/PlayerCharacter.h"

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

void ABulldog::ShotgunReload()
{
	Super::ShotgunReload();
}

void ABulldog::ShotgunReloadStart()
{
	Super::ShotgunReloadStart();

	WeaponReloadAnim->Montage_Play(BulldogMonatge[EShotgunReloadIndex::Start]);

	PlayerRef->Instance->Montage_Play(PlayerRef->BulldogReloadMonatge[EShotgunReloadIndex::Start]);
}

void ABulldog::ShotgunReloadLoop()
{
	Super::ShotgunReloadLoop();

	WeaponReloadAnim->Montage_Play(BulldogMonatge[EShotgunReloadIndex::Loop]);

	PlayerRef->Instance->Montage_Play(PlayerRef->BulldogReloadMonatge[EShotgunReloadIndex::Loop]);

	bIsReloading = true;
}

void ABulldog::ShotgunReloadEnd()
{
	Super::ShotgunReloadEnd();

	WeaponReloadAnim->Montage_Play(BulldogMonatge[EShotgunReloadIndex::End]);

	PlayerRef->Instance->Montage_Play(PlayerRef->BulldogReloadMonatge[EShotgunReloadIndex::End]);

	bIsReloading = false;
}

void ABulldog::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	AmmoData = Instance->BulldogData();

	WeaponReloadAnim = WeaponMesh->GetAnimInstance();
}
