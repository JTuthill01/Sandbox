#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
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
class SANDBOX_API APlayerCharacter : public ACharacter
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Sounds)
	class USoundBase* CharingHandleSound;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AWeaponBase* CurrentWeapon;

	FORCEINLINE UCameraComponent* GetCamera() { return Camera; }
	FORCEINLINE void SetIsReloading(bool IsReloading) { bIsReloading = IsReloading; }
	FORCEINLINE void SetCanFire(bool CanFire) { bCanFire = CanFire; }

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

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float MaxSprintSpeed = 900.F;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* Arms;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<class UAnimMontage*> FireMonatge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<class UAnimMontage*> ReloadMonatge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float BaseTurnRate = 45.F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float BaseLookRate = 45.F;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate = 45.F;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsFirstSlotFull;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsSecondSlotFull;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsThirdSlotFull;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCanFire;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCanReload;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCanSwitchWeapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsReloading;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsChangingWeapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsAiming;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsNearWall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFirstSlotActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSecondSlotActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsThirdSlotActive;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EHasWeapon HasWeaponEnum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float defaultFOV;

	EWeaponSlot EWeaponSlotEnum;

	AWeaponBase* WeaponSlot_01;

	AWeaponBase* WeaponSlot_02;

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
	void Equip();
	
	float DefaultWalkSpeed;
	float AnimTime;
	float ReloadTime;

	bool bShouldBeShown;
};
