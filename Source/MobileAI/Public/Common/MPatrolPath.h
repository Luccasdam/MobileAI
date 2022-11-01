// Code made by Luccas Machado. Feel free to use it anyway you like it!


#pragma once
#include "CoreMinimal.h"
#include "MPatrolPath.generated.h"

class UBillboardComponent;


USTRUCT(BlueprintType)
struct FPatrolPointStruct
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, Category=Gameplay, meta=(MakeEditWidget))
	FVector Location;

	UPROPERTY(EditInstanceOnly, Category=Gameplay)
	float WaitTime;

	UPROPERTY(EditInstanceOnly, Category=Gameplay)
	float WaitTimeRandomDeviation;
};


UCLASS()
class MOBILEAI_API AMPatrolPath : public AActor
{
	GENERATED_BODY()

public:	
	AMPatrolPath();

	// Methods
public:
	FVector GetPatrolLocation(const uint8 PatrolIndex) const;

	/** Return the Closest Patrol Index found by AI */
	uint8 GetClosestPatrolIndex(const FVector& ActorLocation) const;

	/** Try to get the next Patrol Index and return true if succeeded */
	bool GetNextPatrolIndex(uint8& PatrolIndex, bool bReverse) const;
	
	// Components
protected:
	UPROPERTY(VisibleAnywhere, Category=Components)
	UBillboardComponent* BillboardComp;

	// Data
private:
	/** PatrolPoints in the patrol order */
	UPROPERTY(EditInstanceOnly, Category=Gameplay, meta=(MakeEditWidget))
	TArray<FPatrolPointStruct> PatrolPoints;

	/** Should we loop or reverse when reach at last PatrolPoint */
	UPROPERTY(EditInstanceOnly, Category=Gameplay)
	bool bLoop;
	
	/** Distance to define that the Pawn is outside the system */
	UPROPERTY(EditInstanceOnly, Category=Gameplay)
	float PatrolToleranceDistance;
	

	// Inline Getters
public:
	FORCEINLINE float GetPatrolToleranceDistance() const	{ return PatrolToleranceDistance; }
	FORCEINLINE float GetPatrolPointWaitTime(const uint8 PatrolIndex) const	{ return PatrolPoints[PatrolIndex].WaitTime; }
	FORCEINLINE float GetPatrolPointWaitTimeRandomDeviation(const uint8 PatrolIndex) const	{ return PatrolPoints[PatrolIndex].WaitTimeRandomDeviation; }
};