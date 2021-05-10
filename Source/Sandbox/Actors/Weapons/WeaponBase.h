#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/Quat.h"
#include "Sandbox/Structs/STR_AmmoData.h"
#include "Sandbox/Interfaces/Take_Damage.h"
#include "Sandbox/Interfaces/PlayerRef.h"
#include "Sandbox/Interfaces/References.h"
#include "WeaponBase.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8 { TT38, ShortStrokeAR, AmericanShotgun, Bulldog, L86, HandCannon, AK47, SMG, BelgianAR, SKS, XM82 };

UENUM(BlueprintType)
enum class EWeaponClass : uint8 { Pistol, Rifle, Shotgun };

UENUM(BlueprintType)
enum class EFireType : uint8 { Hitscan, Projectile };

enum EShotgunReloadIndex : uint8 { Start, Loop, End };

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

UCLASS()
class SANDBOX_API AWeaponBase : public AActor, public IPlayerRef, public IReferences
{	
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() { return WeaponMesh; }
	FORCEINLINE UMaterialInstance* GetIcon() { return Icon; }
	FORCEINLINE FName GetSocketName() const { return SocketName; }
	FORCEINLINE FName GetWeaponName() const { return WeaponName; }
	FORCEINLINE FHitResult GetHitResult() { return Hit; }

	FORCEINLINE bool GetCanPlayNext() { return bCanPlayNext; }
	FORCEINLINE bool GetIsAiming() const { return bIsAiming; }
	FORCEINLINE int GetTotalMaxAmmo() const { return MaxTotalAmmo; }
	FORCEINLINE int GetCurrentTotalAmmo() { return CurrentTotalAmmo; }
	FORCEINLINE int GetCurrentAmmo() { return CurrentAmmo; }
	FORCEINLINE int32 GetFullMag() { return FullMag; }
	FORCEINLINE float GetKillImpulse() { return KillImpulse; }

	FORCEINLINE void SetCurrentAmmo(int Ammo) { CurrentAmmo = Ammo; }
	FORCEINLINE void SetShouldReload(bool Reload) { bShouldReload = Reload; }
	FORCEINLINE void SetCanPlayNext(bool CanPlay) { bCanPlayNext = CanPlay; }

public:
	UFUNCTION(BlueprintCallable)
	void SetCurrentTotalAmmo(int Ammo);

	UFUNCTION(BlueprintCallable)
	virtual void WeaponReload();

	UFUNCTION(BlueprintCallable)
	virtual void ShotgunReload();

	UFUNCTION(BlueprintCallable)
	virtual void ShotgunReloadStart();

	UFUNCTION(BlueprintCallable)
	virtual void ShotgunReloadLoop();

	UFUNCTION(BlueprintCallable)
	virtual void ShotgunReloadEnd();

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

	virtual AWeaponBase* GetWeaponRef_Implementation() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Enums)
	EWeaponType WeaponType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Enums)
	EWeaponClass WeaponClass;

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

protected:
	UPROPERTY()
	FHitResult Hit;

	UPROPERTY()
	class APlayerCharacter* PlayerRef;

	UPROPERTY()
	class AAICharacter* Character;

	UPROPERTY()
	class AImpactEffects* Impact;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName SocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName WeaponName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Animation)
	class UAnimInstance* WeaponFireAnim;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Animation)
	class UAnimInstance* WeaponReloadAnim;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Animation)
	class UAnimMontage* WeaponFireMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Animation)
	class UAnimMontage* WeaponReloadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Impact)
	TSubclassOf<class AImpactEffects> ImpactEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<class AProjectileBase> SpawnProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	class AProjectileBase* Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VFX)
	class UNiagaraSystem* AmmoEject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VFX)
	class UNiagaraSystem* FireFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class USoundBase* FireSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UMaterialInstance* Icon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAmmoData AmmoData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool bCanPlayNext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ammo)
	int CurrentAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ammo)
	int MaxMagAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ammo)
	int CurrentTotalAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ammo)
	int MaxTotalAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ammo)
	int LowAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ammo)
	bool bShouldReload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int32 FullMag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ReloadTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CriticalHitDamageModifier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RecoilIntensitity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BulletSpread;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float KillImpulse;

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

public:
	bool HasAmmoInMag();
	bool HasExtraAmmo();
	bool HasFullMag();
	bool IsAmmoFull();

protected:
	FQuat EjectQuat;
	FTransform EjectTransform;

	FQuat FireQuat;
	FTransform FireTransform;

	int ReloadCurrentAmmo;
};
