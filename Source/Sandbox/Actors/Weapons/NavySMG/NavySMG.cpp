#include "NavySMG.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox/Instances/SandboxGameInstance.h"

ANavySMG::ANavySMG() = default;

void ANavySMG::WeaponFire(EFireType FireType)
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

void ANavySMG::WeaponReload()
{
	Super::WeaponReload();

	WeaponReloadAnim = WeaponMesh->GetAnimInstance();

	if (WeaponReloadAnim)
	{
		WeaponReloadAnim->Montage_Play(WeaponReloadMontage);
	}
}

void ANavySMG::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	AmmoData = Instance->NavySMGData();
}
