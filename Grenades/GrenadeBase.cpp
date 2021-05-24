#include "GrenadeBase.h"
#include "Components/SphereComponent.h"
#include "Sandbox/Character/PlayerCharacter.h"
#include "../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "Sandbox/AI/AICharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGrenadeBase::AGrenadeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));

	GrenadeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade Mesh"));
	GrenadeMesh->SetupAttachment(SceneRoot);
	GrenadeMesh->SetCastShadow(false);

	DamageSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Damage Sphere"));
	DamageSphere->SetGenerateOverlapEvents(true);
	DamageSphere->SetupAttachment(GrenadeMesh);

	SetRootComponent(SceneRoot);

	FuseLength = 5.F;
}

void AGrenadeBase::OnReleased(FVector ForwardVector)
{
	ForwardVector *= ImpulseForce;

	GrenadeMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	GrenadeMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GrenadeMesh->SetSimulatePhysics(true);
	GrenadeMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	GrenadeMesh->AddImpulse(ForwardVector);

	GetWorldTimerManager().SetTimer(TExplodeHandle, this, &AGrenadeBase::Explode, FuseLength, false);
}

void AGrenadeBase::Explode()
{
	
}

// Called when the game starts or when spawned
void AGrenadeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

