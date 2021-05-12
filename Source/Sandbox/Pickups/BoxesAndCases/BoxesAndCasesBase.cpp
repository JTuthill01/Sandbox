#include "BoxesAndCasesBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sandbox/Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox/Interfaces/PlayerRef.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sandbox/Pickups/PickupBase.h"

// Sets default values
ABoxesAndCasesBase::ABoxesAndCasesBase()
{
	Hull = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hull"));

	Lid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lid"));
	Lid->SetupAttachment(Hull);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetupAttachment(Hull);

	SetRootComponent(Hull);
}

// Called when the game starts or when spawned
void ABoxesAndCasesBase::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABoxesAndCasesBase::InteractBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABoxesAndCasesBase::InteractEnd);
}

void ABoxesAndCasesBase::Open()
{
	Lid->SetSimulatePhysics(true);
	Lid->AddRadialImpulse(MeshLocation, Radius, Strength, ERadialImpulseFalloff::RIF_Linear, true);

	bHasBeenOpened = true;

	GetWorld()->GetTimerManager().SetTimer(RemoveLidTimer, this, &ABoxesAndCasesBase::RemoveLid, TimeToRemove, false);

	Spawn();
}

void ABoxesAndCasesBase::Spawn()
{
	FActorSpawnParameters parms;
	parms.Owner = this;
	parms.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (size_t i = 0; i < Point.Num(); ++i)
	{
		SpawnLocation = Point[i]->GetComponentLocation();

		SpawnRotator = Point[i]->GetComponentRotation();

		for (size_t j = 0; j < SpawnArray.Num(); ++j)
		{
			BasePickup = GetWorld()->SpawnActor<APickupBase>(SpawnArray[j], SpawnLocation, SpawnRotator, parms);

			BasePickup->GetMesh()->SetSimulatePhysics(false);

			if (IsValid(BasePickup))
			{
				BasePickup->SetIsAmmoSuccessful(true);
			}

			else
			{
				BasePickup->SetIsAmmoSuccessful(false);

				break;
			}
		}
	}
}

void ABoxesAndCasesBase::InteractBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

	if (bHasBeenOpened == false)
	{
		AddWidget(OtherActor);
	}

	if (IsValid(Player))
	{
		if (bHasBeenOpened == false)
		{
			Player->OnInteract.AddDynamic(this, &ABoxesAndCasesBase::Open);
		}
	}
}

void ABoxesAndCasesBase::InteractEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

	RemoveWidget(OtherActor);

	if (IsValid(Player))
	{
		Player->OnInteract.RemoveDynamic(this, &ABoxesAndCasesBase::Open);
	}
}

void ABoxesAndCasesBase::RemoveLid() 
{
	Lid->DestroyComponent();

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void ABoxesAndCasesBase::AddWidget_Implementation(AActor* OtherActor){}

void ABoxesAndCasesBase::RemoveWidget_Implementation(AActor* OtherActor){}



