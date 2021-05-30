#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SightAttachment.generated.h"

UCLASS()
class SANDBOX_API ASightAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASightAttachment();

protected:
	UFUNCTION(BlueprintCallable)
	void ActivateForwardRenderTexture(class UTextureRenderTarget2D* LensBehind, class UTextureRenderTarget2D* LensReflection);

	UFUNCTION(BlueprintCallable)
	void ActivateBackRenderTexture(class UTextureRenderTarget2D* Lens_Behind, class UTextureRenderTarget2D* Lens_Reflection);

	UFUNCTION(BlueprintCallable)
	void DisableLensReflection();

	UFUNCTION(BlueprintCallable)
	void EnableLensReflection();

	UFUNCTION(BlueprintCallable)
	void ShowRisAdapter(int32 AdapterID);

	UFUNCTION(BlueprintCallable)
	void ClearAllAdapters();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = RootScene)
	class USceneComponent* RootScene;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* Sight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* Strike_Ironsight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* RIS_Adapter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* RIS_Adapter_Mid;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* RIS_Adapter_High;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Scene)
	class USceneCaptureComponent2D* LensBehindCaptureComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Scene)
	class USceneCaptureComponent2D* LensReflectionCapture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Scene)
	class UMaterialInterface* LensMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Booleans)
	bool bBCloserToFaceSightAtachment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Booleans)
	bool bUseRenderToTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Booleans)
	bool bAim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FOV)
	float FOVAdjust;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FOV)
	float FocalDOFDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FOV)
	FString WeaponAttached;
};
