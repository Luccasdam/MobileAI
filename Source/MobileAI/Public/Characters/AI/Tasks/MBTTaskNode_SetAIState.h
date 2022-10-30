// Code made by Luccas Machado. Feel free to use it anyway you like it!


#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Characters/AI/MAICharacter.h"
#include "MBTTaskNode_SetAIState.generated.h"


/**
 * // TODO: This Task is Temporary for simplicity. Instead of State Machine we should use Gameplay Tags.
 */
UCLASS()
class MOBILEAI_API UMBTTaskNode_SetAIState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMBTTaskNode_SetAIState();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere, Category=AI)
	EAIState NewAIState;
};
