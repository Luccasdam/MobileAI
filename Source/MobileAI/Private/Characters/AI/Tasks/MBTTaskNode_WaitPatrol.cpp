// Code made by Luccas Machado. Feel free to use it anyway you like it!


#include "Characters/AI/Tasks/MBTTaskNode_WaitPatrol.h"
#include "AIController.h"
#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "Common/MPatrolPathFollowerComponent.h"


UMBTTaskNode_WaitPatrol::UMBTTaskNode_WaitPatrol()
{
	NodeName = "Wait Patrol";
	bNotifyTick = true;
}

EBTNodeResult::Type UMBTTaskNode_WaitPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Conditions check
	const APawn* MyPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (MyPawn == nullptr)
		return EBTNodeResult::Failed;
	
	const UMPatrolPathFollowerComponent* PatrolComp = UMPatrolPathFollowerComponent::GetPatrolPathFollowerComp(MyPawn);
	if (PatrolComp == nullptr)
		return EBTNodeResult::Failed;

	const AMPatrolPath* PatrolPath = PatrolComp->GetPatrolPath();
	if (PatrolPath == nullptr)
		return EBTNodeResult::Failed;


	// Setup Wait Time
	const float WaitTime = PatrolPath->GetPatrolPointWaitTime(PatrolComp->GetPatrolIndex());
	const float RandomDeviation = PatrolPath->GetPatrolPointWaitTimeRandomDeviation(PatrolComp->GetPatrolIndex());	
	
	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	MyMemory->RemainingWaitTime = FMath::FRandRange(WaitTime - RandomDeviation, WaitTime + RandomDeviation);

	return EBTNodeResult::InProgress;
}

void UMBTTaskNode_WaitPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	MyMemory->RemainingWaitTime -= DeltaSeconds;

	if (MyMemory->RemainingWaitTime <= 0.0f)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
