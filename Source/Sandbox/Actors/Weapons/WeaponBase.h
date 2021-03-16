#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/Quat.h"
#include "WeaponBase.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8 { TT38, ShortStrokeAR, AmericanShotgun, Bulldog, L86, HandCannon, AK47, SMG, BelgianAR, SKS, XM82 };

UENUM(BlueprintType)
enum class EFireType : uint8 { Hitscan, Projectile };

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AWeaponBase> WeaponType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* IconImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsEquipped;
};

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CriticalHit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DamageRadius;
};


UCLASS()
class SANDBOX_API AWeaponBase : public AActor
{	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	FORCEINLINE UMaterialInstance* GetIcon() { return Icon; }
	FORCEINLINE FName GetSocketName() const { return SocketName; }
	FORCEINLINE bool GetIsAiming() const { return bIsAiming; }
	FORCEINLINE int GetCurrentTotalAmmo() { return CurrentTotalAmmo; }
	 
	UFUNCTION(BlueprintCallable)
	int GetCurrentAmmo() { return CurrentAmmo; }
	
	UFUNCTION(BlueprintCallable)
	int GetTotalAmmo() { return CurrentTotalAmmo; }

	UFUNCTION(BlueprintCallable)
	virtual void WeaponReload();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AutomaticRecoil();

	UFUNCTION(BlueprintCallable)
	virtual void WeaponFire(EFireType FireType);

	UFUNCTION(BlueprintCallable)
	virtual void StopFire();

	UFUNCTION(BlueprintCallable)
	void OnAimEnter();

	UFUNCTION(BlueprintCallable)
	void OnAimExit();

	UFUNCTION(BlueprintCallable)
	void CalculateShot(class UCameraComponent* Camera, class USceneComponent* WMesh, FName WeaponFireSocketName, FHitResult& HitResult, FTransform& ProjectileTransform);

	UFUNCTION(BlueprintCallable)
	void AddDamage(FHitResult HitResult);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Enums)
	EWeaponType WeaponType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Enums)
	EFireType fireType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Sounds)
	class USoundBase* MagInSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Sounds)
	class USoundBase* MagOutSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Sounds)
	class USoundBase* ChargingHandlePull;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName SocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Animation)
	class UAnimInstance* WeaponFireAnim;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Animation)
	class UAnimInstance* WeaponReloadAnim;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Animation)
	class UAnimMontage* WeaponFireMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Animation)
	class UAnimMontage* WeaponReloadMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ammo)
	int CurrentAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ammo)
	int MaxMagAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ammo)
	int CurrentTotalAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ammo)
	int MaxTotalAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ReloadTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CriticalHitDamageModifier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RecoilIntensitity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BulletSpread;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAmmoData AmmoData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsAiming;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bHasMultipleBullets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsAutomatic;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AutomaticFireRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ammo)
	int BulletCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VFX)
	class UNiagaraSystem* AmmoEject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VFX)
	class UNiagaraSystem* FireFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase* FireSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UMaterialInstance* Icon;

	UPROPERTY()
	class APlayerCharacter* PlayerRef;

public:
	bool HasAmmoInMag();
	bool HasExtraAmmo();
	bool HasFullMag();

protected:
	FQuat EjectQuat;
	FTransform EjectTransform;

	FQuat FireQuat;
	FTransform FireTransform;
};
