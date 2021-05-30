#include "SightAttachment.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ASightAttachment::ASightAttachment()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Sight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sight"));
	Strike_Ironsight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Iron Sight"));
	RIS_Adapter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RIS Adapter"));
	RIS_Adapter_Mid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RIS Adapter Mid"));
	RIS_Adapter_High = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RIS Adapter High"));

	LensBehindCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Lens Behind Capture Component"));
	LensReflectionCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Lens Reflection Capture"));

	Sight->SetupAttachment(RootScene);
	Strike_Ironsight->SetupAttachment(RootScene);
	RIS_Adapter->SetupAttachment(RootScene);
	RIS_Adapter_Mid->SetupAttachment(RootScene);
	RIS_Adapter_High->SetupAttachment(RootScene);

	LensBehindCaptureComponent->SetupAttachment(Sight);
	LensReflectionCapture->SetupAttachment(Sight);

	SetRootComponent(RootScene);

	FOVAdjust = 55.F;
}

void ASightAttachment::ActivateForwardRenderTexture(class UTextureRenderTarget2D* LensBehind, class UTextureRenderTarget2D* LensReflection)
{
	LensBehindCaptureComponent->TextureTarget = LensBehind;

	LensReflectionCapture->TextureTarget = LensReflection;
}

void ASightAttachment::ActivateBackRenderTexture(class UTextureRenderTarget2D* Lens_Behind, class UTextureRenderTarget2D* Lens_Reflection)
{
	LensBehindCaptureComponent->TextureTarget = Lens_Behind;

	LensReflectionCapture->TextureTarget = Lens_Reflection;
}

void ASightAttachment::DisableLensReflection()
{
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(LensMaterial, Sight);

	DynMaterial->SetScalarParameterValue("Dust&ReflectionPower", NULL);
}

void ASightAttachment::EnableLensReflection()
{
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(LensMaterial, Sight);

	DynMaterial->SetScalarParameterValue("Dust&ReflectionPower", 1.F);
}

void ASightAttachment::ShowRisAdapter(int32 AdapterID)
{
	switch (AdapterID)
	{
	case 0: 

		RIS_Adapter->SetVisibility(true);

	break;

	case 1:

		RIS_Adapter_Mid->SetVisibility(true);

		break;


	case 2:

		RIS_Adapter_High->SetVisibility(true);

		break;

	default:
		break;
	}
}

void ASightAttachment::ClearAllAdapters()
{
	RIS_Adapter->SetVisibility(false);

	RIS_Adapter_Mid->SetVisibility(false);

	RIS_Adapter_High->SetVisibility(false);
}

