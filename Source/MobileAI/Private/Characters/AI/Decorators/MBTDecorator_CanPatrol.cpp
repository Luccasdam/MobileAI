// Code made by Luccas Machado. Feel free to use it anyway you like it!


#include "Characters/AI/Decorators/MBTDecorator_CanPatrol.h"

#include "AIController.h"
#include "Common/MPatrolPathFollowerComponent.h"

UMBTDecorator_CanPatrol::UMBTDecorator_CanPatrol()
{
	NodeName = "Can Patrol";
}

bool UMBTDecorator_CanPatrol::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (const APawn* MyPawn = OwnerComp.GetAIOwner()->GetPawn())
	{
		if (const UMPatrolPathFollowerComponent* PatrolComp = UMPatrolPathFollowerComponent::GetPatrolPathFollowerComp(MyPawn))
			return PatrolComp->HasPatrolPath();
	}	

	return false;
}
