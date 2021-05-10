#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "Sandbox/Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox/AI/AICharacter.h"
#include "Sandbox/Actors/ImpactEffects/ImpactEffects.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 10000.F;
	ProjectileMovement->MaxSpeed = 10000.F;
	ProjectileMovement->ProjectileGravityScale = 0.2F;
	ProjectileMovement->bSweepCollision = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetSphereRadius(8.F);
	Sphere->SetGenerateOverlapEvents(true);
	Sphere->bReturnMaterialOnMove = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileMesh->SetupAttachment(Sphere);

	SetRootComponent(Sphere);
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = IPlayerRef::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	AICharacterRef = IReferences::Execute_GetAICharacterRef(AAICharacter::StaticClass()->GetDefaultObject());

	ProjectileMovement->OnProjectileStop.AddDynamic(this, &AProjectileBase::ProjectileStop);
}

void AProjectileBase::ProjectileStop(const FHitResult& HitResult)
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform HitTransform = ProjectileMesh->GetComponentTransform();

	if (bIsCausingRadiusDamage == true)
	{
		ExplodeOnImpact(HitResult);

		ProjectileMesh->SetHiddenInGame(true);

		Spawn(HitResult);
	}

	else
	{
		DealDamage(HitResult);

		SpawnImpact(HitResult);

		Destroy();

		Spawn(HitResult);
	}
}

void AProjectileBase::ExplodeOnImpact(const FHitResult& HitResult)
{
	ITake_Damage* iTemp = Cast<ITake_Damage>(AICharacterRef);

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjects;
	TArray<AActor*> ActorsToIgnore;
	TArray<AActor*> OutActors;

	ActorsToIgnore.Add(PlayerRef->CurrentWeapon);
	ActorsToIgnore.Add(this);

	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), HitResult.ImpactPoint, AmmoData.DamageRadius, TraceObjects, NULL, ActorsToIgnore, OutActors);

	uint8 Len = OutActors.Num();

	for (uint8 i = 0; i < Len; ++i)
	{
		OutActors[i] = HitResult.Actor.Get();

		if (iTemp != nullptr)
		{
			if (OutActors[i] != nullptr)
			{
				if (OutActors[i]->GetClass()->ImplementsInterface(UTake_Damage::StaticClass()))
				{
					iTemp->Execute_Take_Damage(OutActors[i], AmmoData, CriticalHitModifier, HitResult);
				}
			}
		}

		else
		{
			return;
		}
	}
}

void AProjectileBase::Spawn(const FHitResult& HitResult)
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector Location = HitResult.ImpactPoint;
	FRotator Rotation = FRotator(0.F);

	//GetWorld()->SpawnActor<AExplosionImpulse>(Impulse, Location, Rotation, Params);
}

void AProjectileBase::DealDamage(const FHitResult& HitResult)
{
	ITake_Damage* iTemp = Cast<ITake_Damage>(AICharacterRef);

	AActor* TempActor = HitResult.Actor.Get();

	if (iTemp != nullptr)
	{
		if (TempActor != nullptr)
		{
			if (TempActor->GetClass()->ImplementsInterface(UTake_Damage::StaticClass()))
			{
				iTemp->Execute_Take_Damage(TempActor, AmmoData, CriticalHitModifier, HitResult);
			}
		}
	}

	else
	{
		return;
	}
}

void AProjectileBase::SpawnImpact(const FHitResult& HitResult)
{
	FTransform TempTransform = ProjectileMesh->GetComponentTransform();

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (HitResult.bBlockingHit == true)
	{
		Effect = GetWorld()->SpawnActorDeferred<AImpactEffects>(EffectToSpawn, TempTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Effect->SetHitResult(HitResult);

		UGameplayStatics::FinishSpawningActor(Effect, TempTransform);
	}
}

AProjectileBase* AProjectileBase::GetProjectileRef_Implementation() { return this; }
