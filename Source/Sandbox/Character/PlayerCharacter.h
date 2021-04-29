#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "Sandbox/Interfaces/Take_Damage.h"
#include "Sandbox/Interfaces/PlayerRef.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteract);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAimEnter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAimExit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStopFire);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFireWeapon, EWeaponType, Weapon);

UENUM(BlueprintType)
enum class EHasWeapon : uint8 { NoWeapon, HasWeapon };

UENUM(BlueprintType)
enum class EWeaponSlot : uint8 { First_Slot, Second_Slot, Third_Slot };

enum EFireMontageToPlay : uint8 { F_TT38, F_ShortStrokeAR, F_AmericanShotgun, F_Bulldog, F_L86, F_HandCannon, F_AK47, F_SMG, F_BelgianAR, F_SKS, F_XM82 };

enum EReloadMontageToPlay : uint8 { R_TT38, R_ShortStrokeAR, R_AmericanShotgun, R_Bulldog, R_L86, R_HandCannon, R_AK47, R_SMG, R_BelgianAR, R_SKS, R_XM82 };

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
	FAimEnter OnAimEnter;

	UPROPERTY(BlueprintAssignable)
	FAimExit OnAimExit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	EHasWeapon HasWeaponEnum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AWeaponBase* CurrentWeapon;

	UFUNCTION(BlueprintCallable)
	bool IsHealthFull();

	UFUNCTION(BlueprintPure)
	void SetIconImage(UMaterialInstance*& Image);

	UFUNCTION(BlueprintCallable)
	void FOnAimEnter();

	UFUNCTION(BlueprintCallable)
	void FOnAimExit();

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void FireAnimationToPlay();

	UFUNCTION(BlueprintCallable)
	void ReloadAnimationToPlay();

	UFUNCTION(BlueprintCallable)
	bool SpawnWeapon(TSubclassOf<AWeaponBase> WeaponToSpawn, bool& bIsSuccessful);

	UFUNCTION(BlueprintCallable)
	FString GetWeaponSlot_01_Name();

	UFUNCTION(BlueprintCallable)
	FString GetWeaponSlot_02_Name();

	FORCEINLINE UCameraComponent* GetCamera() { return Camera; }
	FORCEINLINE int GetCurrentHealth() { return CurrentHealth; }
	FORCEINLINE int GetMaxHealth() { return MaxHealth; }
	FORCEINLINE AWeaponBase* GetCurrentWeapon() { return CurrentWeapon; }
	FORCEINLINE AWeaponBase* GetWeaponSlot_01() { return WeaponSlot_01; }
	FORCEINLINE AWeaponBase* GetWeaponSlot_02() { return WeaponSlot_02; }

	FORCEINLINE void SetIsReloading(bool IsReloading) { bIsReloading = IsReloading; }
	FORCEINLINE void SetCanFire(bool CanFire) { bCanFire = CanFire; }
	FORCEINLINE void SetHealth(int Health) { CurrentHealth += Health; CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth); }
	FORCEINLINE void SetHealthFull() { CurrentHealth = MaxHealth; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ShowWeapon(AWeaponBase* Weapon);

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintCallable)
	void FirePressed();

	UFUNCTION(BlueprintCallable)
	void FireReleased();

	UFUNCTION(BlueprintCallable)
	void RegenerateHealth();

	UFUNCTION(BlueprintCallable)
	void SetFOV(float FOV);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerDeath();

	UFUNCTION(BlueprintCallable)
	void Equip();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float MaxSprintSpeed = 900.F;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PlayerTakeDamage_Implementation(int Damage) override;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AWeaponBase* WeaponSlot_01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AWeaponBase* WeaponSlot_02;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DefaultFOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float BaseTurnRate = 45.F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	FTimerHandle RegenerateHealthTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsNearWall;

	UPROPERTY()
	EWeaponSlot EWeaponSlotEnum;

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
	void DebugTakeDamage();
	
	float DefaultWalkSpeed;
	float AnimTime;
	float ReloadTime;

	bool bShouldBeShown;
};
