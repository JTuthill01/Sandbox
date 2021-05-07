#include "ImpactEffects.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Chaos/ChaosEngineInterface.h"
#include "Sound/SoundBase.h"
#include "Materials/MaterialInterface.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"

// Sets default values
AImpactEffects::AImpactEffects() = default;

AImpactEffects* AImpactEffects::GetImpactRef_Implementation() { return this; }

// Called when the game starts or when spawned
void AImpactEffects::BeginPlay()
{
	Super::BeginPlay();

	SetDecalRotation();

	SpawnFX();

	SpawnSound();

	SpawnDecal();
}

void AImpactEffects::SetDecalRotation()
{
	FVector Normal;
	Normal = HitResult.Normal;
	 
	FRotator TempRotator;
	TempRotator = UKismetMathLibrary::MakeRotFromX(Normal);

	float TempFloat = UKismetMathLibrary::RandomFloatInRange(-180.F, 180.F);

	DecalRotation = UKismetMathLibrary::MakeRotator(TempFloat, TempRotator.Pitch, TempRotator.Yaw);
}

void AImpactEffects::SpawnFX()
{
	FRotator Rotation(0.F);
	FVector Scale(1.F);

	if (HitResult.PhysMaterial != nullptr)
	{
		switch (HitResult.PhysMaterial->SurfaceType)
		{
		case SurfaceType1:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DefaultFX, HitResult.Location, Rotation, Scale);

			break;

		case SurfaceType2:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, HitResult.Location, Rotation, Scale);

			break;

		case SurfaceType3:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, HitResult.Location, Rotation, Scale);

			break;

		case SurfaceType4:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, HitResult.Location, Rotation, Scale);

			break;

		case SurfaceType5:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, HitResult.Location, Rotation, Scale);

			break;

		case SurfaceType6:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, HitResult.Location, Rotation, Scale);

			break;

		case SurfaceType7:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, HitResult.Location, Rotation, Scale);

			break;

		case SurfaceType8:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, HitResult.Location, Rotation, Scale);

			break;

		default:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DefaultFX, HitResult.Location, Rotation, Scale);

			break;
		}
	}
}

void AImpactEffects::SpawnSound()
{
	if (HitResult.bBlockingHit == true && HitResult.PhysMaterial != nullptr)
	{
		switch (HitResult.PhysMaterial->SurfaceType)
		{
		case SurfaceType1:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ConcreteSound, HitResult.Location);

			break;

		case SurfaceType2:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, HitResult.Location);

			break;

		case SurfaceType3:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, HitResult.Location);

			break;

		case SurfaceType4:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, HitResult.Location);

			break;

		case SurfaceType5:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, HitResult.Location);

			break;

		case SurfaceType6:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, HitResult.Location);

			break;

		case SurfaceType7:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, HitResult.Location);

			break;

		case SurfaceType8:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, HitResult.Location);

			break;

		default:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), DefaultSound, HitResult.Location);

			break;
		}
	}
}

void AImpactEffects::SpawnDecal()
{
	FVector DecalVector(DecalSize);

	USceneComponent* TempComponent = Cast<USceneComponent>(HitResult.Component);

	if (HitResult.bBlockingHit == true && HitResult.PhysMaterial != nullptr)
	{
		switch (HitResult.PhysMaterial->SurfaceType)
		{
		case SurfaceType1:
			
			UGameplayStatics::SpawnDecalAttached(ConcreteDecalMaterial, DecalVector, TempComponent, HitResult.BoneName, HitResult.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		case SurfaceType2:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, HitResult.BoneName, HitResult.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		case SurfaceType3:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, HitResult.BoneName, HitResult.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		case SurfaceType4:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, HitResult.BoneName, HitResult.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		case SurfaceType5:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, HitResult.BoneName, HitResult.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		case SurfaceType6:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, HitResult.BoneName, HitResult.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		case SurfaceType7:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, HitResult.BoneName, HitResult.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		case SurfaceType8:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, HitResult.BoneName, HitResult.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;

		default:

			UGameplayStatics::SpawnDecalAttached(DefaultDecalMaterial, DecalVector, TempComponent, HitResult.BoneName, HitResult.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		}
	}
}
