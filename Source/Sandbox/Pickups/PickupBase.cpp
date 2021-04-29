#include "PickupBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sandbox/Interfaces/PlayerRef.h"
#include "Sandbox/Character/PlayerCharacter.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"

// Sets default values
APickupBase::APickupBase()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));

	PickupMesh->SetSimulatePhysics(true);

	SetRootComponent(PickupMesh);

	Sphere->SetupAttachment(PickupMesh);
	Sphere->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = IPlayerRef::Execute_GetPlayerRef(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void APickupBase::SetHealth(EPickupHealthType Type, bool& IsSuccessful, bool& HasBeenPickedUp)
{
	IsSuccessful = bIsSuccessful;

	if (IsValid(PlayerRef))
	{
		if (PlayerRef->IsHealthFull() == false)
		{
			switch (Type)
			{
			case EPickupHealthType::None:
				break;

			case EPickupHealthType::HealthSmall:

				PlayerRef->SetHealth(HealthPackValue);

				HasBeenPickedUp = true;

				break;

			case EPickupHealthType::HealthMedium:

				PlayerRef->SetHealth(HealthPackValue);

				HasBeenPickedUp = true;

				break;

			case EPickupHealthType::HealthLarge:

				PlayerRef->SetHealth(HealthPackValue);

				HasBeenPickedUp = true;

				break;

			default:
				break;
			}
		}

		else
		{
			HasBeenPickedUp = false;
		}
	}

	else
	{
		return;
	}
}

void APickupBase::AmmoPickup(EPickupAmmoType Type, AWeaponBase* CurrentWeapon, AWeaponBase* WeaponSlot_01, AWeaponBase* WeaponSlot_02, bool& IsSuccessful, bool& IsAmmoFull, bool& HasBeenPickedup)
{
	IsSuccessful = bIsAmmoSuccessful;

	HasBeenPickedup = bHasBeenPickedup;

	if (IsValid(PlayerRef->GetCurrentWeapon()))
	{
		if (PlayerRef->GetCurrentWeapon()->IsAmmoFull() == false)
		{
			switch (Type)
			{
			case EPickupAmmoType::None:
				break;

			case EPickupAmmoType::PistolAmmo:

				if (CurrentWeapon->WeaponClass == EWeaponClass::Pistol)
				{
					PlayerRef->GetCurrentWeapon()->SetCurrentTotalAmmo(PistolAmmoValue);

					IsAmmoFull = false;

					HasBeenPickedup = true;
				}

				else if (WeaponSlot_01->WeaponClass == EWeaponClass::Pistol)
				{
					PlayerRef->GetWeaponSlot_01()->SetCurrentTotalAmmo(PistolAmmoValue);

					IsAmmoFull = false;

					HasBeenPickedup = true;
				}

				else if (WeaponSlot_02->WeaponClass == EWeaponClass::Pistol)
				{
					PlayerRef->GetWeaponSlot_02()->SetCurrentTotalAmmo(PistolAmmoValue);

					IsAmmoFull = false;

					HasBeenPickedup = true;
				}

				else
				{
					HasBeenPickedup = false;
				}

				break;

			case EPickupAmmoType::RifleAmmo:

				if (CurrentWeapon->WeaponClass == EWeaponClass::Rifle)
				{
					PlayerRef->GetCurrentWeapon()->SetCurrentTotalAmmo(RifleAmmoValue);

					IsAmmoFull = false;

					HasBeenPickedup = true;
				}

				else if (WeaponSlot_01->WeaponClass == EWeaponClass::Rifle)
				{
					PlayerRef->GetWeaponSlot_01()->SetCurrentTotalAmmo(RifleAmmoValue);

					IsAmmoFull = false;

					HasBeenPickedup = true;
				}

				else if (IsValid(WeaponSlot_02))
				{
					if (WeaponSlot_02->WeaponClass == EWeaponClass::Rifle)
					{
						PlayerRef->GetWeaponSlot_02()->SetCurrentTotalAmmo(RifleAmmoValue);

						IsAmmoFull = false;

						HasBeenPickedup = true;
					}
				}

				else
				{
					HasBeenPickedup = false;
				}

				break;

			case EPickupAmmoType::ShotgunAmmo:

				if (CurrentWeapon->WeaponClass == EWeaponClass::Shotgun)
				{
					PlayerRef->GetCurrentWeapon()->SetCurrentTotalAmmo(ShotgunAmmoValue);

					IsAmmoFull = false;

					HasBeenPickedup = true;
				}

				else if (WeaponSlot_01->WeaponClass == EWeaponClass::Shotgun)
				{
					PlayerRef->GetWeaponSlot_01()->SetCurrentTotalAmmo(ShotgunAmmoValue);

					IsAmmoFull = false;

					HasBeenPickedup = true;
				}

				else if (WeaponSlot_02->WeaponClass == EWeaponClass::Shotgun)
				{
					PlayerRef->GetWeaponSlot_02()->SetCurrentTotalAmmo(ShotgunAmmoValue);

					IsAmmoFull = false;

					HasBeenPickedup = true;
				}

				else
				{
					HasBeenPickedup = false;
				}

				break;

			default:
				break;
			}
		}

		else
		{
			IsAmmoFull = true;

			HasBeenPickedup = false;
		}
	}

	else
	{
		return;
	}
}

void APickupBase::GetCurrentWeapons(AWeaponBase*& CurrentWeapon, AWeaponBase*& Weapon_Slot01, AWeaponBase*& Weapon_Slot02)
{
	CurrentWeapon = PlayerRef->GetCurrentWeapon();

	Weapon_Slot01 = PlayerRef->GetWeaponSlot_01();

	Weapon_Slot02 = PlayerRef->GetWeaponSlot_02();
}
