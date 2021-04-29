#include "ImpactEffects.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Chaos/ChaosEngineInterface.h"
#include "Sound/SoundBase.h"
#include "Materials/MaterialInterface.h"

// Sets default values
AImpactEffects::AImpactEffects() = default;

AImpactEffects* AImpactEffects::GetImpactRef_Implementation() { return this; }

// Called when the game starts or when spawned
void AImpactEffects::BeginPlay()
{
	Super::BeginPlay();
}

void AImpactEffects::SetHitResult(FHitResult Result)
{
	if (Result.bBlockingHit == true)
	{
		SetDecalRotation(Result);

		SpawnFX(Result);

		SpawnSound(Result);

		SpawnDecal(Result);
	}
}

void AImpactEffects::SetDecalRotation(FHitResult Hit)
{
	FVector Normal;
	Normal = Hit.Normal;
	 
	FRotator TempRotator;
	TempRotator = UKismetMathLibrary::MakeRotFromX(Normal);

	float TempFloat = UKismetMathLibrary::RandomFloatInRange(-180.F, 180.F);

	DecalRotation = UKismetMathLibrary::MakeRotator(TempFloat, TempRotator.Pitch, TempRotator.Yaw);
}

void AImpactEffects::SpawnFX(FHitResult Hit)
{
	FRotator Rotation(0.F);
	FVector Scale(1.F);

	if (Hit.PhysMaterial != nullptr)
	{
		switch (Hit.PhysMaterial->SurfaceType)
		{
		case SurfaceType1:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DefaultFX, Hit.Location, Rotation, Scale);

			break;

		case SurfaceType2:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, Hit.Location, Rotation, Scale);

			break;

		case SurfaceType3:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, Hit.Location, Rotation, Scale);

			break;

		case SurfaceType4:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, Hit.Location, Rotation, Scale);

			break;

		case SurfaceType5:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, Hit.Location, Rotation, Scale);

			break;

		case SurfaceType6:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, Hit.Location, Rotation, Scale);

			break;

		case SurfaceType7:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, Hit.Location, Rotation, Scale);

			break;

		case SurfaceType8:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, Hit.Location, Rotation, Scale);

			break;

		default:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DefaultFX, Hit.Location, Rotation, Scale);

			break;
		}
	}
}

void AImpactEffects::SpawnSound(FHitResult Hit)
{
	if (Hit.bBlockingHit == true && Hit.PhysMaterial != nullptr)
	{
		switch (Hit.PhysMaterial->SurfaceType)
		{
		case SurfaceType1:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ConcreteSound, Hit.Location);

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, __FUNCTION__);

			break;

		case SurfaceType2:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, Hit.Location);

			break;

		case SurfaceType3:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, Hit.Location);

			break;

		case SurfaceType4:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, Hit.Location);

			break;

		case SurfaceType5:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, Hit.Location);

			break;

		case SurfaceType6:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, Hit.Location);

			break;

		case SurfaceType7:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, Hit.Location);

			break;

		case SurfaceType8:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, Hit.Location);

			break;

		default:

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), DefaultSound, Hit.Location);

			break;
		}
	}
}

void AImpactEffects::SpawnDecal(FHitResult Hit)
{
	FVector DecalVector(DecalSize);

	USceneComponent* TempComponent = Cast<USceneComponent>(Hit.Component);

	if (Hit.bBlockingHit == true && Hit.PhysMaterial != nullptr)
	{
		switch (Hit.PhysMaterial->SurfaceType)
		{
		case SurfaceType1:
			
			UGameplayStatics::SpawnDecalAttached(ConcreteDecalMaterial, DecalVector, TempComponent, Hit.BoneName, Hit.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		case SurfaceType2:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, Hit.BoneName, Hit.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		case SurfaceType3:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, Hit.BoneName, Hit.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		case SurfaceType4:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, Hit.BoneName, Hit.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		case SurfaceType5:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, Hit.BoneName, Hit.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		case SurfaceType6:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, Hit.BoneName, Hit.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		case SurfaceType7:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, Hit.BoneName, Hit.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		case SurfaceType8:

			UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent, Hit.BoneName, Hit.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;

		default:

			UGameplayStatics::SpawnDecalAttached(DefaultDecalMaterial, DecalVector, TempComponent, Hit.BoneName, Hit.ImpactPoint, DecalRotation, EAttachLocation::KeepWorldPosition, DecalLifeSpan);

			break;
		}
	}
}
