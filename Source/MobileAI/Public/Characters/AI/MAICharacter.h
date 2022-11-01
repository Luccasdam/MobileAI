// Code made by Luccas Machado. Feel free to use it anyway you like it!


#pragma once
#include "CoreMinimal.h"
#include "Characters/MCharacterBase.h"
#include "MAICharacter.generated.h"


class UMPatrolPathFollowerComponent;
class UTextRenderComponent;
class UBehaviorTree;


UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Sleep,
	Guard,
	Suspicious,
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

	// Methods
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetAIState(const EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent)
	void DisplayState(FDisplayStateStruct DisplayStateStruct);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopDisplayState();

	UPROPERTY()
	FOnStateChanged OnStateChanged;

	
	// Components
protected:
	/** To increase modularity, this could be added per AI Character in blueprints */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	UMPatrolPathFollowerComponent* PatrolPathFollowerComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	UTextRenderComponent* TextRenderComp;
	
	
	// Data
protected:
	UPROPERTY(EditDefaultsOnly, Category=AI)
	UBehaviorTree* BT;	

	UPROPERTY(BlueprintReadOnly, Category=AI)
	EAIState AIState;

	UPROPERTY(BlueprintReadOnly, Category=AI)
	FDisplayStateStruct DisplaySleepStruct;

	UPROPERTY(BlueprintReadOnly, Category=AI)
	FDisplayStateStruct DisplaySuspiciousStruct;

	UPROPERTY(BlueprintReadOnly, Category=AI)
	FDisplayStateStruct DisplayAlertStruct;

	// Inline Getters
public:
	FORCEINLINE UBehaviorTree* GetBT() const { return BT; };
	FORCEINLINE EAIState GetAIState() const { return AIState; }
};
