#include "WarHammerPickupBase.h"
#include "Sandbox/Character/PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWarHammerPickupBase::AWarHammerPickupBase()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	HammerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HammerMesh"));

	SetRootComponent(HammerMesh);

	Sphere->SetupAttachment(HammerMesh);
	Sphere->SetGenerateOverlapEvents(true);
}

void AWarHammerPickupBase::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AWarHammerPickupBase::OnBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AWarHammerPickupBase::OnEnd);
}


void AWarHammerPickupBase::OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PlayerRef = Cast<APlayerCharacter>(OtherActor);

	AddWidget(OtherActor);

	if (IsValid(PlayerRef))
	{
		PlayerRef->OnInteract.AddDynamic(this, &AWarHammerPickupBase::SpawnHammer);
	}
}

void AWarHammerPickupBase::OnEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerRef = Cast<APlayerCharacter>(OtherActor);

	RemoveWidget(OtherActor);

	if (IsValid(PlayerRef))
	{
		PlayerRef->OnInteract.RemoveDynamic(this, &AWarHammerPickupBase::SpawnHammer);
	}
}

void AWarHammerPickupBase::SpawnHammer()
{
	bool bIsSuccessful;

	PlayerRef->SpawnHammer(Hammer, bIsSuccessful);

	if (bIsSuccessful == true)
	{
		Destroy();
	}
}

void AWarHammerPickupBase::AddWidget_Implementation(AActor* OtherActor){}

void AWarHammerPickupBase::RemoveWidget_Implementation(AActor* OtherActor){}

