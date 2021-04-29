#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

UENUM(BlueprintType)
enum class EPickupType : uint8 { None, Weapon, Health, Ammo };

UENUM(BlueprintType)
enum class EPickupHealthType : uint8 { None, HealthSmall, HealthMedium, HealthLarge };

UENUM(BlueprintType)
enum class EPickupAmmoType : uint8 { None, PistolAmmo, RifleAmmo, ShotgunAmmo };

UCLASS()
class SANDBOX_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBase();

	FORCEINLINE UStaticMeshComponent* GetMesh() { return PickupMesh; }

	FORCEINLINE void SetIsSuccessful(bool Successful) { bIsSuccessful = Successful; }
	FORCEINLINE void SetIsAmmoSuccessful(bool Successful) { bIsAmmoSuccessful = Successful; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void SetHealth(EPickupHealthType Type, bool& IsSuccessful, bool& HasBeenPickedUp);

	UFUNCTION(BlueprintCallable)
	virtual void AmmoPickup(EPickupAmmoType Type, AWeaponBase* CurrentWeapon, AWeaponBase* WeaponSlot_01, AWeaponBase* WeaponSlot_02, bool& IsSuccessful, bool& IsAmmoFull, bool& HasBeenPickedup);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetCurrentWeapons(AWeaponBase*& CurrentWeapon, AWeaponBase*& Weapon_Slot01, AWeaponBase*& Weapon_Slot02);

protected:
	UPROPERTY()
	class APlayerCharacter* PlayerRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsSuccessful;

	UPROPERTY()
	bool bIsAmmoSuccessful;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bHasBeenPickedup;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USphereComponent* Sphere;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* PickupMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName PickupName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
	TSubclassOf<class AWeaponBase> Weapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Enums)
	EPickupType PickupType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Enums)
	EPickupHealthType PickupHealthType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Enums)
	EPickupAmmoType PickupAmmoType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Health)
	int HealthPackValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ammo)
	int PistolAmmoValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ammo)
	int RifleAmmoValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ammo)
	int ShotgunAmmoValue;
};
