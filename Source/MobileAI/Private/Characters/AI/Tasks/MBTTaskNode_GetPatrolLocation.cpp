// Code made by Luccas Machado. Feel free to use it anyway you like it!


#include "Characters/AI/Tasks/MBTTaskNode_GetPatrolLocation.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Common/MPatrolPathFollowerComponent.h"

UMBTTaskNode_GetPatrolLocation::UMBTTaskNode_GetPatrolLocation()
{
	NodeName = "Get Patrol Location";

	// Only accept Vector Type
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UMBTTaskNode_GetPatrolLocation, BlackboardKey));
}

EBTNodeResult::Type UMBTTaskNode_GetPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Conditions check
	const APawn* MyPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (MyPawn == nullptr)
		return EBTNodeResult::Failed;

	UMPatrolPathFollowerComponent* PatrolComp = UMPatrolPathFollowerComponent::GetPatrolPathFollowerComp(MyPawn);
	if (PatrolComp == nullptr)
		return EBTNodeResult::Failed;

	if (!PatrolComp->HasPatrolPath())
		return EBTNodeResult::Failed;

	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, PatrolComp->GetPatrolLocation());
	return EBTNodeResult::Succeeded;
}
