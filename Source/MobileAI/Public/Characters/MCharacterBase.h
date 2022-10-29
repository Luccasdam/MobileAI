// Code made by Luccas Machado. Feel free to use it anyway you like!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCharacterBase.generated.h"

UCLASS()
class MOBILEAI_API AMCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMCharacterBase();

	FORCEINLINE bool GetCrouching() const { return bCrouching; }
	
protected:
	bool bCrouching;
	
};
