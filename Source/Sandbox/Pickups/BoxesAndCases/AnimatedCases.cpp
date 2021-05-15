#include "AnimatedCases.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Sandbox/Character/PlayerCharacter.h"
#include "Sandbox/Pickups/PickupBase.h"

// Sets default values
AAnimatedCases::AAnimatedCases()
{
	CaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Case Mesh"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

	BoxCollision->SetGenerateOverlapEvents(true);

	BoxCollision->SetupAttachment(CaseMesh);
	SetRootComponent(CaseMesh);
}

// Called when the game starts or when spawned
void AAnimatedCases::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAnimatedCases::InteractBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AAnimatedCases::InteractEnd);
}

void AAnimatedCases::Open()
{
	CaseMesh->PlayAnimation(CaseOpenAnimation, false);

	bHasBeenOpened = true;

	SpawnCasePickups();

	BoxCollision->DestroyComponent();
}

void AAnimatedCases::InteractBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

	AddWidget(OtherActor);

	if (bHasBeenOpened == false)
	{
		if (IsValid(Player))
		{
			Player->OnInteract.AddDynamic(this, &AAnimatedCases::Open);
		}
	}
}

void AAnimatedCases::InteractEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

	if (IsValid(Player))
	{
		Player->OnInteract.RemoveDynamic(this, &AAnimatedCases::Open);

		RemoveWidget(OtherActor);
	}
}

void AAnimatedCases::SpawnCasePickups()
{
	FActorSpawnParameters Parms;
	Parms.Owner = this;
	Parms.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	int32 DefaultIndex = 0;

	for (size_t i = 0; i < NumOfPickupsToSpawn; ++i)
	{
		SpawnLocation = CaseMesh->GetSocketLocation(SocketNameArray[i]);

		SpawnRotator = CaseMesh->GetSocketRotation(SocketNameArray[i]);

		CurrentIndex = FMath::RandRange(0, PickupIndex);

		if (SpawnArray.IsValidIndex(CurrentIndex))
		{
			BasePickup = GetWorld()->SpawnActor<APickupBase>(SpawnArray[CurrentIndex], SpawnLocation, SpawnRotator, Parms);

			BasePickup->GetMesh()->SetSimulatePhysics(false);
		}

		else
		{
			BasePickup = GetWorld()->SpawnActor<APickupBase>(SpawnArray[DefaultIndex], SpawnLocation, SpawnRotator, Parms);

			BasePickup->GetMesh()->SetSimulatePhysics(false);
		}
	}
}

void AAnimatedCases::AddWidget_Implementation(AActor* OtherActor) {}

void AAnimatedCases::RemoveWidget_Implementation(AActor* OtherActor) {}
