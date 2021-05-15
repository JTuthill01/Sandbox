#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox/Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Sandbox/AI/AICharacter.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "UObject/Class.h"
#include "Chaos/ChaosEngineInterface.h"
#include "Sandbox/Actors/ImpactEffects/ImpactEffects.h"
#include "Sandbox/Actors/Projectiles/ProjectileBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetCastShadow(false);
	WeaponMesh->bReturnMaterialOnMove = true;
	SetRootComponent(WeaponMesh);

	RecoilIntensitity = 30.F;
	BulletSpread = 500.F;
	CriticalHitDamageModifier = 1.F;
	KillImpulse = 10000.F;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerRef = IPlayerRef::Execute_GetPlayerRef(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	Character = IReferences::Execute_GetAICharacterRef(AAICharacter::StaticClass()->GetDefaultObject());

	Projectile = IReferences::Execute_GetProjectileRef(AProjectileBase::StaticClass()->GetDefaultObject());
}

void AWeaponBase::SetCurrentTotalAmmo(int Ammo)
{
	CurrentTotalAmmo += Ammo;

	CurrentTotalAmmo = FMath::Clamp(CurrentTotalAmmo, 0, MaxTotalAmmo);
}

void AWeaponBase::WeaponReload()
{
	ReloadCurrentAmmo = MaxMagAmmo - CurrentAmmo;

	CurrentTotalAmmo -= ReloadCurrentAmmo;

	CurrentAmmo = UKismetMathLibrary::Min(MaxMagAmmo, CurrentTotalAmmo);

	bShouldReload = false;

	CurrentAmmo = FMath::Clamp(CurrentAmmo, 0, MaxTotalAmmo);

	CurrentTotalAmmo = FMath::Clamp(CurrentTotalAmmo, 0, MaxTotalAmmo);
}

void AWeaponBase::ShotgunReload()
{
	bShouldReload = false;

	ReloadCurrentAmmo = MaxMagAmmo - CurrentAmmo;

	CurrentTotalAmmo -= ReloadCurrentAmmo;

	CurrentAmmo++;

	CurrentAmmo = FMath::Clamp(CurrentAmmo, 0, MaxTotalAmmo);

	CurrentTotalAmmo = FMath::Clamp(CurrentTotalAmmo, 0, MaxTotalAmmo);
}

void AWeaponBase::ShotgunReloadStart()
{
}

void AWeaponBase::ShotgunReloadLoop()
{
	ShotgunReload();
}

void AWeaponBase::ShotgunReloadEnd()
{
}

void AWeaponBase::WeaponFire(EFireType FireType)
{
	fireType = FireType;

	CurrentAmmo--;

	if (CurrentAmmo <= LowAmmo)
	{
		bShouldReload = true;
	}

	else
	{
		bShouldReload = false;
	}

	FVector Scale = FVector(2.F);

	FRotator Rotation;
	FRotator TempRotator;

	FTransform Transform;
	FTransform LocalTransform;
	FTransform ProjectileTransform;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	switch (FireType)
	{
	case EFireType::Hitscan:

		if (PlayerRef)
		{
			LocalTransform = UKismetMathLibrary::MakeTransform(Hit.Location, TempRotator, Scale);

			if (bHasMultipleBullets == true)
			{
				for (size_t i = 0; i < BulletCount - 1; ++i)
				{
					CalculateShot(PlayerRef->GetCamera(), WeaponMesh, SocketName, Hit, Transform);

					Impact = GetWorld()->SpawnActorDeferred<AImpactEffects>(ImpactEffects, LocalTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

					Impact->SetHitResult(Hit);

					UGameplayStatics::FinishSpawningActor(Impact, LocalTransform);
		
					AddDamage(Hit);
				}

				if (bIsAutomatic == true)
				{
					AutomaticRecoil();
				}
			}

			else
			{
				CalculateShot(PlayerRef->GetCamera(), WeaponMesh, SocketName, Hit, Transform);

				AImpactEffects* TempImpact = GetWorld()->SpawnActorDeferred<AImpactEffects>(ImpactEffects, LocalTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

				TempImpact->SetHitResult(Hit);

				UGameplayStatics::FinishSpawningActor(TempImpact, LocalTransform);

				AddDamage(Hit);
			}

		}

		break;

	case EFireType::Projectile:
		
		if (bHasMultipleBullets == true)
		{
			for (auto& ProjectileSpawn : ProjectileArray)
			{
				CalculateShot(PlayerRef->GetCamera(), WeaponMesh, "Fire_FX_Slot", Hit, Transform);

				AddDamage(Hit);

				Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileSpawn, Transform, SpawnInfo);
			}
		}

		else
		{
			CalculateShot(PlayerRef->GetCamera(), WeaponMesh, "Fire_FX_Slot", Hit, Transform);

			Projectile = GetWorld()->SpawnActor<AProjectileBase>(SpawnProjectile, Transform, SpawnInfo);

			AddDamage(Hit);
		}
		
		break;

	default:
		break;
	}
}

void AWeaponBase::StopFire()
{
	//TODO Stuff
}

void AWeaponBase::CalculateShot(class UCameraComponent* Camera, class USceneComponent* WMesh, FName WeaponFireSocketName, FHitResult& HitResult, FTransform& ProjectileTransform)
{
	UCameraComponent* LocalCameraComponent = Camera;
	USceneComponent* LocalWeaponMesh = WMesh;
	FName LocalSocketName = WeaponFireSocketName;
	FHitResult LocalHitResult = HitResult;
	FTransform LocalTransform;

	FVector StartLocation;
	FRotator EndLocation;
	FVector TempVector;
	FVector TVector;

	float TempFloat;
	float FloatX;
	float FloatY;
	float FloatZ;
	float TFloat;
	float Spread;
	float Spread1;
	float Spread2;
	float Spread3;

	StartLocation = LocalCameraComponent->GetComponentLocation();
	EndLocation = LocalCameraComponent->GetComponentRotation();

	TempVector = UKismetMathLibrary::GetForwardVector(EndLocation) * 10000.0;
	TVector = TempVector + StartLocation;

	TempFloat = BulletSpread * -1.F;
	TFloat = UKismetMathLibrary::RandomFloatInRange(TempFloat, BulletSpread);

	Spread = BulletSpread * -1.F;
	Spread1 = UKismetMathLibrary::RandomFloatInRange(Spread, BulletSpread);

	Spread2 = BulletSpread * -1.F;
	Spread3 = UKismetMathLibrary::RandomFloatInRange(Spread2, BulletSpread);

	FloatX = TVector.X + TFloat;
	FloatY = TVector.Y + Spread1;
	FloatZ = TVector.Z + Spread3;

	FVector EndVector(FloatX, FloatY, FloatZ);
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjects;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(UGameplayStatics::GetPlayerController(PlayerRef, 0));
	ActorsToIgnore.Add(this);

	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

	FVector SocketLocation = LocalWeaponMesh->GetSocketLocation(LocalSocketName);

	FVector Scale(1.F, 1.F, 1.F);

	if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), StartLocation, EndVector, TraceObjects, true, ActorsToIgnore, EDrawDebugTrace::None, LocalHitResult, true) == true)
	{
		FRotator TempRotator;
		TempRotator = UKismetMathLibrary::FindLookAtRotation(SocketLocation, LocalHitResult.ImpactPoint);

		LocalTransform = UKismetMathLibrary::MakeTransform(SocketLocation, TempRotator, Scale);
	}

	else
	{
		FRotator TempRotator;
		AActor* TempActor = LocalCameraComponent->GetOwner();
		APawn* TempPawn;

		TempPawn = Cast<APawn>(TempActor);

		TempRotator = TempPawn->GetControlRotation();

		LocalTransform = UKismetMathLibrary::MakeTransform(SocketLocation, TempRotator, Scale);
	}

	HitResult = LocalHitResult;

	ProjectileTransform = LocalTransform;
}

void AWeaponBase::AddDamage(FHitResult HitResult)
{
	ITake_Damage* iTemp = Cast<ITake_Damage>(Character);

	AActor* TempActor = HitResult.Actor.Get();

	if (iTemp != nullptr)
	{
		if (TempActor != nullptr)
		{
			if (TempActor->GetClass()->ImplementsInterface(UTake_Damage::StaticClass()))
			{
				iTemp->Execute_Take_Damage(TempActor, AmmoData, CriticalHitDamageModifier, HitResult);
			}
		}
	}
}

bool AWeaponBase::HasAmmoInMag()
{
	if (CurrentAmmo > 0)
	{
		return true;
	}

	return false;
}

bool AWeaponBase::HasExtraAmmo()
{
	if (CurrentTotalAmmo > 0)
	{
		return true;
	}

	return false;
}

bool AWeaponBase::HasFullMag()
{
	if (CurrentAmmo == MaxMagAmmo)
	{
		return true;
	}

	return false;
}

bool AWeaponBase::IsAmmoFull()
{
	if (CurrentTotalAmmo == MaxTotalAmmo)
	{
		return true;
	}

	return false;
}

AWeaponBase* AWeaponBase::GetWeaponRef_Implementation(){ return this; }

void AWeaponBase::AutomaticRecoil_Implementation() {}

void AWeaponBase::OnAimEnter() { bIsAiming = true; }

void AWeaponBase::OnAimExit() { bIsAiming = false; }
