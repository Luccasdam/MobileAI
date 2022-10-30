// Code made by Luccas Machado. Feel free to use it anyway you like it!


#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MBTTaskNode_IntruderAlert.generated.h"


/**
 * 
 */
UCLASS()
class MOBILEAI_API UMBTTaskNode_IntruderAlert : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMBTTaskNode_IntruderAlert();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere, Category=AI)
	FBlackboardKeySelector PlayerKey;
};
