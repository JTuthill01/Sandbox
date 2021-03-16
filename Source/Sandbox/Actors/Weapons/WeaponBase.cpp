#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox/Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetCastShadow(false);
	SetRootComponent(WeaponMesh);

	RecoilIntensitity = 30.F;
	BulletSpread = 500.F;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AWeaponBase::WeaponReload()
{
	int Temp = MaxMagAmmo - CurrentAmmo;

	CurrentTotalAmmo -= Temp;

	CurrentAmmo = UKismetMathLibrary::Min(MaxMagAmmo, CurrentTotalAmmo);
}

void AWeaponBase::WeaponFire(EFireType FireType)
{
	fireType = FireType;

	CurrentAmmo--;

	FHitResult Hit;

	FRotator Rotation;
	FRotator TempRotator;

	FTransform Transform;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	switch (FireType)
	{
	case EFireType::Hitscan:

		if (PlayerRef)
		{
			if (bHasMultipleBullets == true)
			{
				for (int i = 0; i < BulletCount - 1; i++)
				{
					CalculateShot(PlayerRef->GetCamera(), WeaponMesh, SocketName, Hit, Transform);

					//GetWorld()->SpawnActor<AImpactEffects>(ImpactEffects, Transform, SpawnInfo);

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

				//GetWorld()->SpawnActor<AImpactEffects>(ImpactEffects, Transform, SpawnInfo);

				AddDamage(Hit);

				if (bIsAutomatic == true)
				{
					AutomaticRecoil();
				}
			}

		}

		break;

	case EFireType::Projectile:

		CalculateShot(PlayerRef->GetCamera(), WeaponMesh, "Fire_FX_Slot", Hit, Transform);

		//GetWorld()->SpawnActor<AProjectileBase>(Projectile, Transform, SpawnInfo);

		if (bIsAutomatic == true)
		{
			AutomaticRecoil();
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
	FHitResult Hit = HitResult;
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
	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

	FVector SocketLocation = LocalWeaponMesh->GetSocketLocation(LocalSocketName);

	FVector Scale(1.F, 1.F, 1.F);

	if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), StartLocation, EndVector, TraceObjects, true, ActorsToIgnore, EDrawDebugTrace::Persistent, Hit, true) == true)
	{
		FRotator TempRotator;
		TempRotator = UKismetMathLibrary::FindLookAtRotation(SocketLocation, Hit.ImpactPoint);

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

	HitResult = Hit;

	ProjectileTransform = LocalTransform;
}

void AWeaponBase::AddDamage(FHitResult HitResult)
{
	//IINT_TakeDamage::TakeDamage(AmmoData, 0.F, CriticalHitDamageModifier, HitResult);
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

void AWeaponBase::AutomaticRecoil_Implementation() {}

void AWeaponBase::OnAimEnter() { bIsAiming = true; }

void AWeaponBase::OnAimExit() { bIsAiming = false; }
