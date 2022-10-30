// Code made by Luccas Machado. Feel free to use it anyway you like it!


#include "Characters/AI/Tasks/MBTTaskNode_IntruderAlert.h"
#include "Core/MGameModeBase.h"


UMBTTaskNode_IntruderAlert::UMBTTaskNode_IntruderAlert()
{
	NodeName = "Intruder Alert";
	PlayerKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UMBTTaskNode_IntruderAlert, PlayerKey), AActor::StaticClass());
}

EBTNodeResult::Type UMBTTaskNode_IntruderAlert::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (BBComp == nullptr)
		return EBTNodeResult::Failed;

	if (AMGameModeBase* MGameMode = Cast<AMGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		MGameMode->ReportPlayerDetected();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
