// // Code made by Luccas Machado. Feel free to use it anyway you like it!


#include "Characters/AI/Tasks/MBTTaskNode_ClearKey.h"

#include "BehaviorTree/BlackboardComponent.h"

UMBTTaskNode_ClearKey::UMBTTaskNode_ClearKey()
{
	NodeName = "Clear Key Value";
}

EBTNodeResult::Type UMBTTaskNode_ClearKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (BB == nullptr)
		return EBTNodeResult::Failed;
		
	BB->ClearValue(KeyToClear.SelectedKeyName);
	return EBTNodeResult::Succeeded;
}
