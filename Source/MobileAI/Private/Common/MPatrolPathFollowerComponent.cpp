// Code made by Luccas Machado. Feel free to use it anyway you like it!


#include "Common/MPatrolPathFollowerComponent.h"


UMPatrolPathFollowerComponent::UMPatrolPathFollowerComponent()
	: bReverse(false)
	, CurrentPatrolIndex(UINT8_MAX)
{}

UMPatrolPathFollowerComponent* UMPatrolPathFollowerComponent::GetPatrolPathFollowerComp(const APawn* TargetPawn)
{
	return Cast<UMPatrolPathFollowerComponent>(TargetPawn->GetComponentByClass(StaticClass()));
}

FVector UMPatrolPathFollowerComponent::GetPatrolLocation()
{
	if (CurrentPatrolIndex == UINT8_MAX)
	{
		CurrentPatrolIndex = PatrolPath->GetClosestPatrolIndex(GetOwner()->GetActorLocation());
		return PatrolPath->GetPatrolLocation(CurrentPatrolIndex);
	}
	else
	{
		if (PatrolPath->GetNextPatrolIndex(CurrentPatrolIndex, bReverse))
			return PatrolPath->GetPatrolLocation(CurrentPatrolIndex);

		bReverse = !bReverse;
	}

	return GetPatrolLocation();
}

