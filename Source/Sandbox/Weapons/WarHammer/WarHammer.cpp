#include "WarHammer.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInterface.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sandbox/Interfaces/Take_Damage.h"

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
	
	//CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AWarHammer::OnBegin);
	CollisionCapsule->OnComponentEndOverlap.AddDynamic(this, &AWarHammer::OnEnd);
	CollisionCapsule->OnComponentHit.AddDynamic(this, &AWarHammer::OnHammerStrike);
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
	
}

void AWarHammer::OnHammerStrike(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* TempActor = Hit.Actor.Get();

	ITake_Damage* iTemp = Cast<ITake_Damage>(TempActor);

	if (iTemp != nullptr)
	{
		if (TempActor != nullptr)
		{
			if (TempActor->GetClass()->ImplementsInterface(UTake_Damage::StaticClass()))
			{
				iTemp->Execute_Take_Melee_Damage(TempActor, 10, Hit);
			}
		}
	}
}

void AWarHammer::OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
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

