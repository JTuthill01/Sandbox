#include "DestructibleProps.h"
#include "DestructibleComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ADestructibleProps::ADestructibleProps()
{
 	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible Component"));
	DestructibleComponent->SetupAttachment(RootScene);
	DestructibleComponent->SetNotifyRigidBodyCollision(true);


	SetRootComponent(RootScene);

	bIsDestroyed = false;

	Maxhealth = 10.F;

	DefaultDamage = 1.F;
	DefaultImpulse = 1.F;
}

void ADestructibleProps::Take_Melee_Damage_Implementation(int32 DamageToTake, FHitResult HitResult)
{
	float Temp = static_cast<float>(DamageToTake);

	CurrentHealth -= Temp;

	if (CurrentHealth <= 0.F)
	{
		Destroy(DamageToTake, HitResult.Location, HitResult.ImpactPoint, DefaultImpulse);
	}
}

void ADestructibleProps::Destroy(float Damage, FVector HitLocation, FVector ImpulseDirection, float Impulse)
{
	if (!bIsDestroyed)
	{
		bIsDestroyed = true;

		DestructibleComponent->ApplyDamage(DefaultDamage, HitLocation, ImpulseDirection, Impulse);
	}
}

// Called when the game starts or when spawned
void ADestructibleProps::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = Maxhealth;
}
