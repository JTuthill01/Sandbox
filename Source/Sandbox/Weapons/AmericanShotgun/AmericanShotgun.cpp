#include "AmericanShotgun.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox/Instances/SandboxGameInstance.h"
#include "Sandbox/Character/PlayerCharacter.h"

AAmericanShotgun::AAmericanShotgun() = default;

void AAmericanShotgun::WeaponFire(EFireType FireType)
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

void AAmericanShotgun::WeaponReload()
{
	Super::WeaponReload();
}

void AAmericanShotgun::ShotgunReload()
{
	Super::ShotgunReload();
}

void AAmericanShotgun::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	AmmoData = Instance->AmericanShotgunData();

	WeaponReloadAnim = WeaponMesh->GetAnimInstance();
}

void AAmericanShotgun::ShotgunReloadStart()
{
	Super::ShotgunReloadStart();

	WeaponReloadAnim->Montage_Play(AmericanReloadMonatge[EShotgunReloadIndex::Start]);

	PlayerRef->Instance->Montage_Play(PlayerRef->AmericanShotgunReloadMonatge[EShotgunReloadIndex::Start]);
}

void AAmericanShotgun::ShotgunReloadLoop()
{
	Super::ShotgunReloadLoop();

	WeaponReloadAnim->Montage_Play(AmericanReloadMonatge[EShotgunReloadIndex::Loop]);

	PlayerRef->Instance->Montage_Play(PlayerRef->AmericanShotgunReloadMonatge[EShotgunReloadIndex::Loop]);

	bIsReloading = true;
}

void AAmericanShotgun::ShotgunReloadEnd()
{
	Super::ShotgunReloadEnd();

	WeaponReloadAnim->Montage_Play(AmericanReloadMonatge[EShotgunReloadIndex::End]);

	PlayerRef->Instance->Montage_Play(PlayerRef->AmericanShotgunReloadMonatge[EShotgunReloadIndex::End]);
	
	bIsReloading = false;
}
