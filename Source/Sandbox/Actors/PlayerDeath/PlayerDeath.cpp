#include "PlayerDeath.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
APlayerDeath::APlayerDeath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));

	LeftForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("Left Force"));

	RightForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("Right Force"));

	SetRootComponent(Cube);
}

// Called when the game starts or when spawned
void APlayerDeath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerDeath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

