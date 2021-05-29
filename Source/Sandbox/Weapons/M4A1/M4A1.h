#pragma once

#include "CoreMinimal.h"
#include "Sandbox/Actors/Weapons/WeaponBase.h"
#include "M4A1.generated.h"

UCLASS()
class SANDBOX_API AM4A1 : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AM4A1();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attachments)
	class UStaticMeshComponent* CarryingHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attachments)
	class UStaticMeshComponent* GasTube;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attachments)
	class UStaticMeshComponent* Stock;

protected:
	void WeaponFire(EFireType FireType) override;

	void WeaponReload() override;

	void BeginPlay() override;
};
