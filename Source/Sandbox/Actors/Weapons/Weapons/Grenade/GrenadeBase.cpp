#include "GrenadeBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AGrenadeBase::AGrenadeBase()
{
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));

	SetRootComponent(CapsuleCollision);
}

// Called when the game starts or when spawned
void AGrenadeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

