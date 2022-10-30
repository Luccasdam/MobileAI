// Code made by Luccas Machado. Feel free to use it anyway you like it!


#include "Characters/AI/Tasks/MBTTaskNode_SetAIState.h"
#include "AIController.h"


UMBTTaskNode_SetAIState::UMBTTaskNode_SetAIState()
{
	NodeName = "Set AI State";
}

EBTNodeResult::Type UMBTTaskNode_SetAIState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* MyAIC = OwnerComp.GetAIOwner();

	if (AMAICharacter* MAICharacter = Cast<AMAICharacter>(MyAIC->GetCharacter()))
	{
		MAICharacter->SetAIState(NewAIState);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
