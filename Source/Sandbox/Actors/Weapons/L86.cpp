#include "L86.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox/Instances/SandboxGameInstance.h"

AL86::AL86()
{
	Sight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sight"));
	Sight->SetCastShadow(false);
	Sight->SetupAttachment(WeaponMesh, "SightAttachmentPoint");
}

void AL86::WeaponFire(EFireType FireType)
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

void AL86::WeaponReload()
{
	Super::WeaponReload();

	WeaponReloadAnim = WeaponMesh->GetAnimInstance();

	if (WeaponReloadAnim)
	{
		WeaponReloadAnim->Montage_Play(WeaponReloadMontage);
	}
}

void AL86::BeginPlay()
{
	Super::BeginPlay();

	USandboxGameInstance* Instance = Cast<USandboxGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	AmmoData = Instance->L86Data();
}
