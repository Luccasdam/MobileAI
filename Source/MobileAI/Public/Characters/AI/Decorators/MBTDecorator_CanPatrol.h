// Code made by Luccas Machado. Feel free to use it anyway you like it!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MBTDecorator_CanPatrol.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEAI_API UMBTDecorator_CanPatrol : public UBTDecorator
{
	GENERATED_BODY()

public:
	UMBTDecorator_CanPatrol();

private:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
