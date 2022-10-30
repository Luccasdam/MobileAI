// Code made by Luccas Machado. Feel free to use it anyway you like it!


#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MAnimInstance.generated.h"


/**
 *
 */
UCLASS()
class MOBILEAI_API UMAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(Transient, BlueprintReadOnly, Category=Animation)
	bool bCrouching;

	UPROPERTY(Transient, BlueprintReadOnly, Category=Animation)
	float WalkingSpeed;
};
