// Code made by Luccas Machado. Feel free to use it anyway you like it!


#include "Common/MPatrolPath.h"
#include "Components/BillboardComponent.h"
#include "MobileAI/MobileAI.h"

DEFINE_LOG_CATEGORY(LogPatrol);

AMPatrolPath::AMPatrolPath()
	: bLoop(true)
	, PatrolToleranceDistance(100.f)
{
	BillboardComp = CreateDefaultSubobject<UBillboardComponent>("BillboardComp");
	SetRootComponent(BillboardComp);
}

FVector AMPatrolPath::GetPatrolLocation(const uint8 PatrolIndex) const	{ return GetActorLocation() + PatrolPoints[PatrolIndex].Location; }

uint8 AMPatrolPath::GetClosestPatrolIndex(const FVector& ActorLocation) const
{
	if (PatrolPoints.Num() > 1)
	{
		uint8 BestIndex = 0;
		float ClosestDistance = FVector::Distance(GetActorLocation() + PatrolPoints[0].Location, ActorLocation);

		for (uint8 i = 1; i < PatrolPoints.Num(); i++)
		{
			const float Distance = FVector::Distance(GetActorLocation() + PatrolPoints[i].Location, ActorLocation);
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				BestIndex = i;
			}
		}
		return BestIndex;
	}

	UE_LOG(LogPatrol, Warning, TEXT("PatrolSystem: Trying to get ClosestPatrol but there should be at least 2 Locations"))
	return 0;
}

bool AMPatrolPath::GetNextPatrolIndex(uint8& PatrolIndex, bool bReverse) const
{
	// In case reach the path end
	if (PatrolIndex == 0 && bReverse || PatrolIndex == PatrolPoints.Num()-1 && !bReverse)
	{
		if (bLoop)
		{
			PatrolIndex = bReverse ? PatrolPoints.Num()-1 : 0;
			return true;
		}
		return false;
	}
	
	PatrolIndex = bReverse ? PatrolIndex-1 : PatrolIndex+1;
	return true;
}