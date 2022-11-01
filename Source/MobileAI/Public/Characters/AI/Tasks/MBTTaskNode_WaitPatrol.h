// Code made by Luccas Machado. Feel free to use it anyway you like it!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MBTTaskNode_WaitPatrol.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEAI_API UMBTTaskNode_WaitPatrol : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMBTTaskNode_WaitPatrol();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	float RemainingWaitTime;
};
