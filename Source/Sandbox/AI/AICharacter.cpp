#include "AICharacter.h"
#include "Math/UnrealMathUtility.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Sandbox/Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Sandbox/Pickups/PickupBase.h"

// Sets default values
AAICharacter::AAICharacter()
{
	GetMesh()->bReturnMaterialOnMove = true;

	MaxHealth = 100.F;
	CurrentHealth = MaxHealth;

	bIsDead = false;

	HealthPickup = nullptr;
}

AAICharacter* AAICharacter::GetAICharacterRef_Implementation() { return this; }

void AAICharacter::SetDamage(float Damage, float CriticalHitChance, float CriticalDamageModifier, FHitResult HitResult, float& DamageToApply, bool& bWasCritical)
{
	bool bIsCritical = false;

	float DamageAmount = Damage;

	if (CriticalHitChance < FMath::RandRange(0.F, 100.F))
	{
		bIsCritical = true;

		if (bIsCritical == true)
		{
			DamageAmount *= CriticalDamageModifier;
		}
	}

	DamageAmount *= HitResult.PhysMaterial->DestructibleDamageThresholdScale;

	DamageToApply = DamageAmount;

	bWasCritical = bIsCritical;
}

void AAICharacter::UpdateHealth(float Damage, bool& IsDead)
{
	if (Damage >= CurrentHealth)
	{
		IsDead = true;
		
		CurrentHealth = 0.F;
	}

	else
	{
		CurrentHealth -= Damage;
	}
}

void AAICharacter::Dead(FVector ImpactPoint, FName BoneName)
{
	FVector TempPlayerLocation = PlayerRef->GetActorLocation();

	FVector TempAILocation = AAICharacter::GetActorLocation();

	FVector TempUnitDirection = UKismetMathLibrary::GetDirectionUnitVector(TempPlayerLocation, TempAILocation);

	FVector TempImpulseLocation(0.F);

	float TempKillImpulse = PlayerRef->CurrentWeapon->GetKillImpulse();

	if (PlayerRef->HasWeaponEnum == EHasWeapon::HasWeapon)
	{
		TempImpulseLocation = TempUnitDirection * TempKillImpulse;
	}
	
	else
	{
		TempImpulseLocation = TempUnitDirection * 10000.F;
	}

	OnDeathSpawnHealth();

	OnDeathSpawnAmmo();

	OnDeathSpawnWeapon();

	GetMesh()->SetSimulatePhysics(true);

	GetMesh()->AddImpulseAtLocation(TempImpulseLocation, ImpactPoint, BoneName);

	GetCapsuleComponent()->DestroyComponent();
}

void AAICharacter::OnDeathSpawnHealth()
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector TempAILocation = GetMesh()->GetComponentLocation();

	FRotator TempRotator = GetMesh()->GetComponentRotation();

	HealthPickupChance = FMath::RandRange(0, 150);

	for (size_t i = 0; i < HealthArray.Num(); ++i)
	{
		if (HealthPickupChance < 35)
		{
			HealthPickup = GetWorld()->SpawnActor<APickupBase>(HealthArray[EHealthPickup::SmallHealthPickup], TempAILocation, TempRotator, Params);

			if (IsValid(HealthPickup))
			{
				if (PlayerRef->IsHealthFull() == false)
				{
					HealthPickup->SetIsSuccessful(true);
				}

				else
				{
					HealthPickup->SetIsSuccessful(false);
				}
			}

			else
			{
				HealthPickup->SetIsSuccessful(false);
			}
		}

		else if (HealthPickupChance < 25)
		{
			HealthPickup = GetWorld()->SpawnActor<APickupBase>(HealthArray[EHealthPickup::MediumHealthPickup], TempAILocation, TempRotator, Params);

			if (IsValid(HealthPickup))
			{
				if (PlayerRef->IsHealthFull() == false)
				{
					HealthPickup->SetIsSuccessful(true);
				}

				else
				{
					HealthPickup->SetIsSuccessful(false);
				}
			}

			else
			{
				HealthPickup->SetIsSuccessful(false);
			}
		}

		else if (HealthPickupChance < 15)
		{
			HealthPickup = GetWorld()->SpawnActor<APickupBase>(HealthArray[EHealthPickup::LargeHealthPickup], TempAILocation, TempRotator, Params);

			if (IsValid(HealthPickup))
			{
				if (PlayerRef->IsHealthFull() == false)
				{
					HealthPickup->SetIsSuccessful(true);
				}

				else
				{
					HealthPickup->SetIsSuccessful(false);
				}
			}

			else
			{
				HealthPickup->SetIsSuccessful(false);
			}
		}
	}
}

void AAICharacter::OnDeathSpawnAmmo()
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector TempAILocation = GetMesh()->GetComponentLocation();

	FRotator TempRotator = GetMesh()->GetComponentRotation();

	uint8 NumberOfPickupsToDrop = FMath::RandRange(1, 6);

	for (size_t i = 0; i < NumberOfPickupsToDrop; ++i)
	{
		AmmoPickupChance = FMath::RandRange(0, 100);

		if (AmmoPickupChance > 60)
		{
			AmmoPickup = GetWorld()->SpawnActor<APickupBase>(AmmoArray[EAmmoPickup::PistolAmmoPickup], TempAILocation, TempRotator, Params);

			if (IsValid(AmmoPickup))
			{
				AmmoPickup->SetIsAmmoSuccessful(true);
			}

			else
			{
				AmmoPickup->SetIsAmmoSuccessful(false);
			}
		}

		else if (AmmoPickupChance > 50)
		{
			AmmoPickup = GetWorld()->SpawnActor<APickupBase>(AmmoArray[EAmmoPickup::RifleAmmoPickup], TempAILocation, TempRotator, Params);

			if (IsValid(AmmoPickup))
			{
				AmmoPickup->SetIsAmmoSuccessful(true);
			}

			else
			{
				AmmoPickup->SetIsAmmoSuccessful(false);
			}
		}

		else if (AmmoPickupChance > 40)
		{
			AmmoPickup = GetWorld()->SpawnActor<APickupBase>(AmmoArray[EAmmoPickup::ShotgunAmmoPickup], TempAILocation, TempRotator, Params);

			if (IsValid(AmmoPickup))
			{
				AmmoPickup->SetIsAmmoSuccessful(true);
			}

			else
			{
				AmmoPickup->SetIsAmmoSuccessful(false);
			}
		}
	}
}

void AAICharacter::OnDeathSpawnWeapon()
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector TempAILocation = GetMesh()->GetComponentLocation();

	FRotator TempRotator = GetMesh()->GetComponentRotation();

	uint8 WeaponSpawnChance = FMath::RandRange(0, 100);
	uint8 WeaponToSpawn = FMath::RandRange(0, 10);

	if (WeaponSpawnChance > 30)
	{
		WeaponPickup = GetWorld()->SpawnActor<APickupBase>(WeaponArray[WeaponToSpawn], TempAILocation, TempRotator, Params);
	}
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = IPlayerRef::Execute_GetPlayerRef(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AAICharacter::Take_Damage_Implementation(FAmmoData Ammo_Data, float CriticalHitModifer, FHitResult HitResult)
{
	float TempDamage = 0.F;

	bool bTempBool = false;

	SetDamage(Ammo_Data.Damage, Ammo_Data.CriticalHit, CriticalHitModifer, HitResult, TempDamage, bTempBool);

	UpdateHealth(TempDamage, bIsDead);

	if (bIsDead == true)
	{
		Dead(HitResult.ImpactPoint, HitResult.BoneName);
	}
}


