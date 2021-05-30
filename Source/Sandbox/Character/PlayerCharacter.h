#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "Sandbox/Interfaces/Take_Damage.h"
#include "Sandbox/Interfaces/PlayerRef.h"
#include "Sandbox/Enums/Enums.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteract);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStopFire);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShotgunReload);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFireWeapon, EWeaponType, Weapon);

UCLASS()
class SANDBOX_API APlayerCharacter : public ACharacter, public ITake_Damage, public IPlayerRef
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(BlueprintAssignable)
	FInteract OnInteract;

	UPROPERTY(BlueprintAssignable)
	FStopFire OnStopFire;

	UPROPERTY(BlueprintAssignable)
	FFireWeapon OnFireWeapon;

	UPROPERTY(BlueprintAssignable)
	FShotgunReload OnShotgunReload;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	EHasWeapon HasWeaponEnum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	AWeaponBase* CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TArray<class UAnimMontage*> AmericanShotgunReloadMonatge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TArray<class UAnimMontage*> BulldogReloadMonatge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TArray<class UAnimMontage*> ItalianShotgunReloadMonatge;

	UPROPERTY()
	UAnimInstance* Instance;

public:
	UFUNCTION(BlueprintCallable)
	bool IsHealthFull();

	UFUNCTION(BlueprintCallable)
	void SpawnWeapon(TSubclassOf<AWeaponBase> WeaponToSpawn, bool& IsSuccessful);

	UFUNCTION(BlueprintCallable)
	void SwapWeapon(TSubclassOf<AWeaponBase> WeaponToSpawn, bool& bIsSuccessful);

	UFUNCTION(BlueprintCallable)
	void SpawnHammer(TSubclassOf<class AWarHammer> HammerToSpawn, bool& bIsSuccessful);

	UFUNCTION(BlueprintPure)
	void SetIconImage(UMaterialInstance*& Image);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void CanSwitchWeapon(bool& CanSwitch);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DamageTaken();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateShotgunAmmo();

	UFUNCTION(BlueprintCallable)
	void HideHammer(bool ShouldHide);

	UFUNCTION(BlueprintCallable)
	void SpawnPickup();

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void FireAnimationToPlay();

	UFUNCTION(BlueprintCallable)
	void ReloadAnimationToPlay();

	UFUNCTION(BlueprintCallable)
	void OnGrenadeReleased();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	void CurrentWeaponName(FName& NameOfWeapon);

	FORCEINLINE UCameraComponent* GetCamera() { return Camera; }
	FORCEINLINE AWeaponBase* GetCurrentWeapon() { return CurrentWeapon; }
	FORCEINLINE AWeaponBase* GetWeaponSlot_01() { return WeaponSlot_01; }
	FORCEINLINE AWeaponBase* GetWeaponSlot_02() { return WeaponSlot_02; }
	FORCEINLINE EWeaponType GetWeaponType() { return CurrentWeaponType; }
	FORCEINLINE int GetCurrentHealth() { return CurrentHealth; }
	FORCEINLINE int GetMaxHealth() { return MaxHealth; }

	FORCEINLINE void SetIsReloading(bool IsReloading) { bIsReloading = IsReloading; }
	FORCEINLINE void SetCanFire(bool CanFire) { bCanFire = CanFire; }
	FORCEINLINE void SetHealth(int Health) { CurrentHealth += Health; CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth); }
	FORCEINLINE void SetHealthFull() { CurrentHealth = MaxHealth; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UFUNCTION(BlueprintCallable)
	void ShowWeapon(AWeaponBase* Weapon);

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintCallable)
	void FirePressed();

	UFUNCTION(BlueprintCallable)
	void FireReleased();

	UFUNCTION(BlueprintCallable)
	void ADSPressed();

	UFUNCTION(BlueprintCallable)
	void ADSReleased();

	UFUNCTION(BlueprintCallable)
	void RegenerateHealth();

	UFUNCTION(BlueprintCallable)
	void SetFOV(float FOV);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerDeath();

	UFUNCTION(BlueprintCallable)
	void Equip();

	UFUNCTION(BlueprintCallable)
	void DebugTakeDamage();

	UFUNCTION(BlueprintCallable)
	void ThrowGrenade();

	UFUNCTION(BlueprintCallable)
	void ScanForPickups();

	UFUNCTION()
	void PlayADS_Idle();

	UFUNCTION()
	void PlayADS_Fire();

	UFUNCTION()
	void PlayADS_Walk();

	UFUNCTION()
	void StopADS_Walk();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float MaxSprintSpeed = 900.F;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PlayerTakeDamage_Implementation(int Damage) override;

	virtual void OnDealExplosiveDamage_Implementation(FHitResult HitResult, int32 DamageToApply) override;

	virtual void TakeGernadeDamage_Implementation(int32 DamageToApply) override;

	virtual APlayerCharacter* GetPlayerRef_Implementation() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* Arms;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<class UAnimMontage*> FireMonatge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<class UAnimMontage*> ReloadMonatge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<class UAnimMontage*> MeleeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<class UAnimMontage*> ADSMontage_Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<class UAnimMontage*> ADSMontage_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<class UAnimMontage*> ADSMontage_Walk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* GrenadeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float ADSBlendOutTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AWeaponBase* WeaponSlot_01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AWeaponBase* WeaponSlot_02;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponType CurrentWeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "War Hammer")
	class AWarHammer* HammerSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	class APickupBase* Pickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<class APickupBase> PickupInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TArray< TSubclassOf<class APickupBase>> WeaponPickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	int32 PickupIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	bool bShouldSpawnPickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoxesAndCases")
	TSubclassOf<class ABoxesAndCasesBase> CaseRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimatedCases")
	TSubclassOf<class AAnimatedCases> AnimatedCaseRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grenade)
	class AGrenadeBase* Grenade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grenade)
	TSubclassOf<class AGrenadeBase> GrenadeToSpawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FOV")
	float DefaultFOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float BaseTurnRate = 45.F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float BaseLookRate = 45.F;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate = 45.F;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Health)
	float RegenerativeHealthRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Health)
	int CurrentHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Health)
	int MaxHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Armor)
	int CurrentArmor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Armor)
	int MaxArmor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Health)
	bool bIsDead;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	bool bIsFirstSlotFull;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	bool bIsSecondSlotFull;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	bool bIsThirdSlotFull;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	bool bIsFiring;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	bool bCanFire;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	bool bCanReload;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	bool bIsEmpty;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	bool bCanSwitchWeapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	bool bIsReloading;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	bool bIsChangingWeapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	bool bIsAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	bool bIsFirstSlotActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	bool bIsSecondSlotActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	bool bIsThirdSlotActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 LoopIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	FTimerHandle RegenerateHealthTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsNearWall;

	UPROPERTY()
	EWeaponSlot EWeaponSlotEnum;

	UPROPERTY()
	int32 ShotgunClassIndex;

	UPROPERTY()
	bool bCanUseADS_Idle;

	UPROPERTY()
	bool bCanUseADS_Fire;

	UPROPERTY()
	bool bCanUseADS_Walk;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveUp(float Value);
	void Turn(float Value);
	void TurnRate(float Value);
	void LookUp(float Value);
	void LookUpRate(float Value);

	void StartJump();
	void StopJump();
	void StartSprint();
	void StopSprint();
	void Interact();
	void Melee();
	void CheckForInteraction(AActor* HitActor, FHitResult& HitResult);
	
	float DefaultWalkSpeed;
	float AnimTime;
	float ReloadTime;
	float PickupTimer;

	bool bShouldBeShown;

	FTimerHandle PickupTimerHandle;
};
