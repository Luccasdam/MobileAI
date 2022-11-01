// Code made by Luccas Machado. Feel free to use it anyway you like it!


#include "Common/MPatrolPathFollowerComponent.h"
#include "MobileAI/MobileAI.h"


UMPatrolPathFollowerComponent::UMPatrolPathFollowerComponent()
	: bReverse(false)
	, CurrentPatrolIndex(UINT8_MAX)
{}

UMPatrolPathFollowerComponent* UMPatrolPathFollowerComponent::GetPatrolPathFollowerComp(const APawn* TargetPawn)
{
	UE_LOG(LogPatrol, Log, TEXT("GetPatrolFollowerComp"))
	return Cast<UMPatrolPathFollowerComponent>(TargetPawn->GetComponentByClass(UMPatrolPathFollowerComponent::StaticClass()));
}

FVector UMPatrolPathFollowerComponent::GetPatrolLocation()
{
	if (!HasPatrolPath())
		UE_LOG(LogPatrol, Warning, TEXT("Trying to get PatrolLocation but PatrolPath is not valid"))
	
	// Initializing Patrol
	if (CurrentPatrolIndex == UINT8_MAX)
	{
		UE_LOG(LogPatrol, Log, TEXT("No Patrol index, getting the closest one and returning location"))
		CurrentPatrolIndex = PatrolPath->GetClosestPatrolIndex(GetOwner()->GetActorLocation());
		return PatrolPath->GetPatrolLocation(CurrentPatrolIndex);
	}

	// Get Next Patrol Index if Valid
	if (PatrolPath->GetNextPatrolIndex(CurrentPatrolIndex, bReverse))
	{
		UE_LOG(LogPatrol, Log, TEXT("Next Patrol index is valid, returning location"))
		return PatrolPath->GetPatrolLocation(CurrentPatrolIndex);
	}

	// Case there's no Next Patrol Index, we should switch path follow direction
	UE_LOG(LogPatrol, Log, TEXT("There's no Next Patrol index, switchin direction"))
	bReverse = !bReverse;
	
	return GetPatrolLocation();
}
