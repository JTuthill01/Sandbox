#include "WarHammer.h"
#include "Components/CapsuleComponent.h"
#include "Sandbox/Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sandbox/AI/AICharacter.h"
#include "Sandbox/Interfaces/References.h"
#include "Materials/MaterialInterface.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AWarHammer::AWarHammer()
{
	HammerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hammer"));
	HammerMesh->SetCastShadow(false);

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	CollisionCapsule->SetupAttachment(HammerMesh);
	CollisionCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionCapsule->SetGenerateOverlapEvents(true);
	CollisionCapsule->bReturnMaterialOnMove = true;

	SetRootComponent(HammerMesh);
}

void AWarHammer::BeginPlay()
{
	Super::BeginPlay();

	AICharacter = IReferences::Execute_GetAICharacterRef(AAICharacter::StaticClass()->GetDefaultObject());
	
	CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AWarHammer::OnBegin);
	CollisionCapsule->OnComponentEndOverlap.AddDynamic(this, &AWarHammer::OnEnd);
	//CollisionCapsule->OnComponentHit.AddDynamic(this, &AWarHammer::OnHammerStrike);
}

void AWarHammer::SpawnImpact(FHitResult HitResult)
{
	SetDecalLocation(HitResult);

	FRotator Rotation(0.F);
	FVector Scale(1.F);

	FVector DecalVector(DecalSize);

	USceneComponent* TempComponent = Cast<USceneComponent>(HitResult.Component);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, HitResult.Location, Rotation, Scale);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound, HitResult.Location);

	UGameplayStatics::SpawnDecalAttached(FleshDecalMaterial, DecalVector, TempComponent);
}

void AWarHammer::AddHit(FHitResult HitResult)
{
	ITake_Damage* iTemp = Cast<ITake_Damage>(AICharacter);

	AActor* TempActor = HitResult.Actor.Get();

	if (iTemp != nullptr)
	{
		if (TempActor != nullptr)
		{
			if (TempActor->GetClass()->ImplementsInterface(UTake_Damage::StaticClass()))
			{
				iTemp->Execute_Take_Melee_Damage(TempActor, 10, HitResult);
			}
		}
	}
}

void AWarHammer::OnHammerStrike(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AAICharacter* Character = Cast<AAICharacter>(OtherActor);

	if (IsValid(Character))
	{
		AddHit(Hit);

		SpawnImpact(Hit);

		GEngine->AddOnScreenDebugMessage(-1, 6.F, FColor::Purple, Hit.GetActor()->GetName());
	}
}

void AWarHammer::OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAICharacter* Character = Cast<AAICharacter>(OtherActor);

	//SpawnImpact(SweepResult);

	if (IsValid(Character))
	{
		AddHit(SweepResult);
	}
}

void AWarHammer::OnEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AWarHammer::SetDecalLocation(FHitResult Result)
{
	FVector Normal;
	Normal = Result.Normal;

	FRotator TempRotator;
	TempRotator = UKismetMathLibrary::MakeRotFromX(Normal);

	float TempFloat = UKismetMathLibrary::RandomFloatInRange(-180.F, 180.F);

	DecalRotation = UKismetMathLibrary::MakeRotator(TempFloat, TempRotator.Pitch, TempRotator.Yaw);
}

