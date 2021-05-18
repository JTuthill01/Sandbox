#include "ExplosivePropsBase.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Components/CapsuleComponent.h"
#include "Sandbox/Character/PlayerCharacter.h"
#include "Sandbox/Interfaces/PlayerRef.h"
#include "Sandbox/Interfaces/Take_Damage.h"

// Sets default values
AExplosivePropsBase::AExplosivePropsBase()
{
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));

	ExplosiveProp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Explosive Prop"));
	ExplosiveProp->SetupAttachment(Capsule);

	SetRootComponent(Capsule);

	CurrentHealth = 20;

	DamageRadius = 300.F;
}

 AExplosivePropsBase* AExplosivePropsBase::GetExplosivePropRef_Implementation(){ return this; }

// Called when the game starts or when spawned
void AExplosivePropsBase::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerRef = IPlayerRef::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AExplosivePropsBase::OnPropHit_Implementation(int32 DamageToTake, FHitResult HitResult)
{
	int32 TempDamage = 0;

	SetDamage(DamageToTake, HitResult, TempDamage);

	UpdateHealth(TempDamage, bIsDead);

	if (bIsDead == true)
	{
		Dead();
	}
}

void AExplosivePropsBase::SetDamage(int32 Damage, FHitResult HitResult, int32& DamageToApply)
{
	int32 DamageAmount = Damage;

	DamageAmount *= HitResult.PhysMaterial->DestructibleDamageThresholdScale;

	DamageToApply = DamageAmount;
}

void AExplosivePropsBase::UpdateHealth(int32 Damage, bool& IsDead)
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

void AExplosivePropsBase::Dead()
{
	FVector TempVector = GetActorLocation();

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionFX, TempVector);

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosiveSound, TempVector);

	Destroy();
}
