// Code made by Luccas Machado. Feel free to use it anyway you like it!


#pragma once
#include "CoreMinimal.h"
#include "Characters/MCharacterBase.h"
#include "MAICharacter.generated.h"

class UBehaviorTree;
class UTextRenderComponent;


UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Sleep,
	Guard,
	Alert
};


USTRUCT(BlueprintType)
struct FDisplayStateStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString DisplayText;

	UPROPERTY(BlueprintReadOnly)
	float PlayRate;

	UPROPERTY(BlueprintReadOnly)
	float DisplayTime;

	UPROPERTY(BlueprintReadOnly)
	bool bLoop;
};


/**
 * 
 */
UCLASS(Abstract)
class MOBILEAI_API AMAICharacter : public AMCharacterBase
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnStateChanged, const EAIState, NewAIState);

public:
	AMAICharacter();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetAIState(const EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent)
	void DisplayState(FDisplayStateStruct DisplayStateStruct);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopDisplayState();

	UPROPERTY()
	FOnStateChanged OnStateChanged;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Components)
	UTextRenderComponent* TextRenderComp;
	
	UPROPERTY(EditDefaultsOnly, Category=AI)
	UBehaviorTree* BT;	

	UPROPERTY(BlueprintReadOnly, Category=AI)
	EAIState AIState;

	UPROPERTY(BlueprintReadOnly, Category=AI)
	FDisplayStateStruct DisplaySleepStruct;

	UPROPERTY(BlueprintReadOnly, Category=AI)
	FDisplayStateStruct DisplayAlertStruct;

public:
	FORCEINLINE UBehaviorTree* GetBT() const { return BT; };
	FORCEINLINE EAIState GetAIState() const { return AIState; }
};
