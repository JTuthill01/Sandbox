#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify_PlaySound.h"
#include "MagOutNotify_PlaySound.generated.h"

UCLASS()
class SANDBOX_API UMagOutNotify_PlaySound : public UAnimNotify_PlaySound
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
