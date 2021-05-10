#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimMontage.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetStringLibrary.h"
#include "Sandbox/Interfaces/References.h"
#include "Sandbox/Pickups/PickupBase.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(GetRootComponent());

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	Arms->SetupAttachment(Camera);
	Arms->SetCastShadow(false);

	bCanFire = true;
	bCanSwitchWeapon = true;
	bCanReload = true;

	DefaultFOV = 90.F;

	ReloadTime = 1.5F;

	MaxHealth = 100;
	CurrentHealth = MaxHealth;

	MaxArmor = 100;
	CurrentArmor = MaxArmor;

	RegenerativeHealthRate = 25.F;

	ShotgunClassIndex = static_cast<int32>(EWeaponClass::Shotgun);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	CurrentWeapon = IReferences::Execute_GetWeaponRef(AWeaponBase::StaticClass()->GetDefaultObject());

	Instance = Arms->GetAnimInstance();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &APlayerCharacter::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &APlayerCharacter::TurnRate);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &APlayerCharacter::LookUpRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &APlayerCharacter::StopJump);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &APlayerCharacter::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &APlayerCharacter::StopSprint);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerCharacter::FirePressed);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &APlayerCharacter::FireReleased);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Released, this, &APlayerCharacter::SpawnPickup);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &APlayerCharacter::Reload);
	PlayerInputComponent->BindAction(TEXT("Damage"), IE_Pressed, this, &APlayerCharacter::DebugTakeDamage);
	PlayerInputComponent->BindAction(TEXT("ADS"), IE_Pressed, this, &APlayerCharacter::FOnAimEnter);
	PlayerInputComponent->BindAction(TEXT("ADS"), IE_Released, this, &APlayerCharacter::FOnAimExit);
}

void APlayerCharacter::PlayerTakeDamage_Implementation(int Damage)
{
	GetWorld()->GetTimerManager().ClearTimer(RegenerateHealthTimer);

	if (bIsDead == false)
	{
		if (CurrentArmor <= Damage)
		{
			int TempDamage = Damage - CurrentArmor;

			CurrentHealth = FMath::Clamp(CurrentHealth - TempDamage, 0, MaxHealth);

			CurrentArmor = 0;

			if (CurrentHealth <= 0)
			{
				bIsDead = true;

				PlayerDeath();
			}
		}

		else
		{
			CurrentArmor -= Damage;
		}

		GetWorld()->GetTimerManager().SetTimer(RegenerateHealthTimer, this, &APlayerCharacter::RegenerateHealth, 5.F, true);
	}
}

void APlayerCharacter::ShowWeapon(AWeaponBase* Weapon)
{
	if (IsValid(Weapon))
	{
		if (Weapon != WeaponSlot_01)
		{
			WeaponSlot_01->SetActorHiddenInGame(true);

			if (Weapon == WeaponSlot_02)
			{
				WeaponSlot_02->SetActorHiddenInGame(false);
			}
		}

		else if (Weapon == WeaponSlot_01)
		{
			WeaponSlot_01->SetActorHiddenInGame(false);
		}
	}
}

void APlayerCharacter::SpawnWeapon(TSubclassOf<AWeaponBase > WeaponToSpawn, bool& bIsSuccessful)
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector Location = GetMesh()->GetComponentLocation();

	FRotator Rotation = GetMesh()->GetComponentRotation();

	switch (EWeaponSlotEnum)
	{
	case EWeaponSlot::First_Slot:

		if (!bIsFirstSlotFull)
		{
			WeaponSlot_01 = GetWorld()->SpawnActor<AWeaponBase>(WeaponToSpawn, Location, Rotation, Params);

			if (IsValid(WeaponSlot_01))
			{
				WeaponSlot_01->AttachToComponent(Arms, FAttachmentTransformRules::SnapToTargetIncludingScale,
					WeaponSlot_01->GetSocketName());

				bIsFirstSlotFull = true;

				CurrentWeapon = WeaponSlot_01;

				HasWeaponEnum = EHasWeapon::HasWeapon;

				ShowWeapon(CurrentWeapon);

				bIsSuccessful = true;

				bIsFirstSlotActive = true;

				bIsSecondSlotActive = false;
			}
		}

		else if (!bIsSecondSlotFull)
		{
			EWeaponSlotEnum = EWeaponSlot::Second_Slot;

			SpawnWeapon(WeaponToSpawn, bIsSuccessful);
		}

		else
		{
			bIsSuccessful = false;
		}

		break;

	case EWeaponSlot::Second_Slot:

		if (!bIsSecondSlotFull)
		{
			WeaponSlot_02 = GetWorld()->SpawnActor<AWeaponBase>(WeaponToSpawn, Location, Rotation, Params);

			if (IsValid(WeaponSlot_02))
			{
				WeaponSlot_02->AttachToComponent(Arms, FAttachmentTransformRules::SnapToTargetIncludingScale,
					WeaponSlot_02->GetSocketName());

				bIsSecondSlotFull = true;

				CurrentWeapon = WeaponSlot_02;

				HasWeaponEnum = EHasWeapon::HasWeapon;

				ShowWeapon(CurrentWeapon);

				bIsSuccessful = true;

				bIsSecondSlotActive = true;

				bIsFirstSlotActive = false;				
			}
		}

		else if (!bIsFirstSlotFull)
		{
			EWeaponSlotEnum = EWeaponSlot::First_Slot;

			SpawnWeapon(WeaponToSpawn, bIsSuccessful);
		}

		else
		{
			bIsSuccessful = false;
		}

		break;

	case EWeaponSlot::Third_Slot:
		break;

	default:
		break;
	}
}

void APlayerCharacter::Fire()
{
	int32 WeaponIndex = static_cast<int32>(CurrentWeapon->WeaponClass);

	if (bCanFire == true && bIsReloading == false && bIsChangingWeapon == false)
	{
		if (CurrentWeapon->HasAmmoInMag() == true)
		{
			CurrentWeapon->WeaponFire(CurrentWeapon->fireType);

			OnFireWeapon.Broadcast(CurrentWeapon->WeaponType);

			FireAnimationToPlay();

			bIsFiring = true;
		}

		else if (WeaponIndex != ShotgunClassIndex)
		{
			if (CurrentWeapon->HasAmmoInMag() == false)
			{
				if (CurrentWeapon->HasExtraAmmo() == true)
				{
					bCanReload = true;

					Reload();

					CurrentWeapon->SetShouldReload(false);
				}
			}
		}

		else
		{
			if (CurrentWeapon->HasAmmoInMag() == false)
			{
				if (CurrentWeapon->HasExtraAmmo() == true)
				{
					bCanReload = true;

					CurrentWeapon->SetShouldReload(false);
				}
			}
		}
	}

	if (CurrentWeapon->GetCurrentTotalAmmo() <= 0)
	{
		bIsEmpty = true;
	}
}

void APlayerCharacter::SwapWeapon(TSubclassOf<AWeaponBase> WeaponToSpawn, bool& IsSuccessful)
{
	if (IsValid(CurrentWeapon))
	{
		if (bIsReloading == false && bIsFiring == false && bIsChangingWeapon == false)
		{
			if (CurrentWeapon == WeaponSlot_01)
			{
				PickupIndex = static_cast<int32>(WeaponSlot_01->WeaponType);

				CurrentWeapon->Destroy();

				CurrentWeapon = WeaponSlot_02;

				bIsFirstSlotFull = false;

				WeaponSlot_01 = nullptr;

				SpawnWeapon(WeaponToSpawn, IsSuccessful);
			}

			else if (CurrentWeapon == WeaponSlot_02)
			{
				PickupIndex = static_cast<int32>(WeaponSlot_02->WeaponType);

				CurrentWeapon->Destroy();

				CurrentWeapon = WeaponSlot_01;

				bIsSecondSlotFull = false;

				WeaponSlot_02 = nullptr;

				SpawnWeapon(WeaponToSpawn, IsSuccessful);
			}
		}
	}
}

void APlayerCharacter::SpawnPickup()
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector LocationVector = Arms->GetComponentLocation();

	FRotator LocationRotator = Arms->GetComponentRotation();

	if (bShouldSpawnPickup == true)
	{
		Pickup = GetWorld()->SpawnActor<APickupBase>(WeaponPickup[PickupIndex], LocationVector, LocationRotator, Params);
	}
}

void APlayerCharacter::Reload()
{
	int32 WeaponIndex = static_cast<int32>(CurrentWeapon->WeaponClass);

	if (bCanReload == true && CurrentWeapon->GetCurrentTotalAmmo() > 0)
	{
		bIsEmpty = false;

		if (bIsReloading == false && bIsChangingWeapon == false)
		{
			if (WeaponIndex == ShotgunClassIndex)
			{
				OnShotgunReload.Broadcast();
			}

			else if (CurrentWeapon->HasFullMag() == false)
			{
				bIsReloading = true;

				bCanFire = false;

				CurrentWeapon->WeaponReload();

				CurrentWeapon->SetShouldReload(false);

				ReloadAnimationToPlay();
			}
		}
	}

	if (CurrentWeapon->GetCurrentTotalAmmo() <= 0)
	{
		bIsEmpty = true;
	}
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.F)
	{
		AddMovementInput(GetActorForwardVector() * Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.F)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerCharacter::MoveUp(float Value)
{
	if (Value != 0.F)
	{
		AddMovementInput(GetActorUpVector(), Value);
	}
}

void APlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::TurnRate(float Value)
{
	AddControllerPitchInput(Value);
}

void APlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value * BaseLookRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::Equip()
{
	if (bIsReloading == false || bCanFire == false)
	{
		if (CurrentWeapon != WeaponSlot_01 && bIsFirstSlotFull == true)
		{
			WeaponSlot_02->SetActorHiddenInGame(true);

			WeaponSlot_01->SetActorHiddenInGame(false);

			CurrentWeapon = WeaponSlot_01;

			if (CurrentWeapon->GetCurrentTotalAmmo() > 0)
			{
				bIsEmpty = false;
			}

			else
			{
				bIsEmpty = true;
			}
		}

		else if (CurrentWeapon != WeaponSlot_02 && bIsSecondSlotFull == true)
		{
			WeaponSlot_01->SetActorHiddenInGame(true);

			WeaponSlot_02->SetActorHiddenInGame(false);

			CurrentWeapon = WeaponSlot_02;

			if (CurrentWeapon->GetCurrentTotalAmmo() > 0)
			{
				bIsEmpty = false;
			}

			else
			{
				bIsEmpty = true;
			}
		}

		else if (bIsSecondSlotFull == false)
		{
			CurrentWeapon = WeaponSlot_01;
		}
	}
}

void APlayerCharacter::CanSwitchWeapon(bool& CanSwitch)
{
	if (bIsFirstSlotFull == true && bIsSecondSlotFull == true)
	{
		CanSwitch = true;
	}

	else
	{
		CanSwitch = false;
	}
}

void APlayerCharacter::DebugTakeDamage()
{
	ITake_Damage* iTemp = Cast<ITake_Damage>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (iTemp != nullptr)
	{
		iTemp->Execute_PlayerTakeDamage(this, 24);
	}
}

void APlayerCharacter::FirePressed()
{
	switch (HasWeaponEnum)
	{
	case EHasWeapon::NoWeapon:
		break;

	case EHasWeapon::HasWeapon:

		Fire();

		break;

	default:
		break;
	}
}

void APlayerCharacter::FireReleased()
{
	switch (HasWeaponEnum)
	{
	case EHasWeapon::NoWeapon:
		break;

	case EHasWeapon::HasWeapon:

		StopFire();

		break;

	default:
		break;
	}
}

void APlayerCharacter::RegenerateHealth()
{
	if (CurrentHealth < MaxHealth && bIsDead == false)
	{
		float Temp = RegenerativeHealthRate / 6.F;

		CurrentHealth = FMath::Clamp(CurrentHealth + static_cast<int>(Temp), 0, MaxHealth);

		if (CurrentHealth >= MaxHealth)
		{
			GetWorld()->GetTimerManager().ClearTimer(RegenerateHealthTimer);
		}
	}
}

void APlayerCharacter::SetFOV(float FOV)
{
	Camera->SetFieldOfView(FOV);
}

bool APlayerCharacter::IsHealthFull()
{
	if (CurrentHealth == MaxHealth)
	{
		return true;
	}

	return false;
}

void APlayerCharacter::StopFire()
{
	CurrentWeapon->StopFire();

	OnStopFire.Broadcast();

	bIsFiring = false;

	LoopIndex = CurrentWeapon->GetCurrentAmmo();
}

void APlayerCharacter::FireAnimationToPlay()
{
	UAnimInstance* LocalInstance = Arms->GetAnimInstance();

	int32 WeaponIndex = static_cast<int32>(CurrentWeapon->WeaponType);

	if (FireMonatge.IsValidIndex(WeaponIndex))
	{
		LocalInstance->Montage_Play(FireMonatge[WeaponIndex]);
	}
}

void APlayerCharacter::ReloadAnimationToPlay()
{
	UAnimInstance* LocalInstance = Arms->GetAnimInstance();

	int32 WeaponIndex = static_cast<int32>(CurrentWeapon->WeaponType);
	int32 ShotgunIndex = static_cast<int32>(CurrentWeapon->WeaponClass);

	if (ShotgunIndex != ShotgunClassIndex)
	{
		if (ReloadMonatge.IsValidIndex(WeaponIndex))
		{
			LocalInstance->Montage_Play(ReloadMonatge[WeaponIndex]);
		}
	}
}

void APlayerCharacter::CurrentWeaponName(FName& NameOfWeapon)
{
	if (CurrentWeapon == WeaponSlot_01)
	{
		NameOfWeapon = WeaponSlot_01->GetWeaponName();
	}

	else if (CurrentWeapon == WeaponSlot_02)
	{
		NameOfWeapon = WeaponSlot_02->GetWeaponName();
	}
}

void APlayerCharacter::SetIconImage(UMaterialInstance*& Image)
{
	if (IsValid(CurrentWeapon))
	{
		Image = CurrentWeapon->GetIcon();
	}
}

APlayerCharacter* APlayerCharacter::GetPlayerRef_Implementation() { return this; }

void APlayerCharacter::FOnAimEnter() { OnAimEnter.Broadcast(); }

void APlayerCharacter::FOnAimExit() { OnAimExit.Broadcast(); }

void APlayerCharacter::Interact() { OnInteract.Broadcast(); }

void APlayerCharacter::StartJump() { Jump(); }

void APlayerCharacter::StopJump() { StopJumping(); }

void APlayerCharacter::StartSprint() { GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed; }

void APlayerCharacter::StopSprint() { GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed; }