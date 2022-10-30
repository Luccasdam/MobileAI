// Code made by Luccas Machado. Feel free to use it anyway you like it!


#pragma once
#include "CoreMinimal.h"
#include "MPatrolPath.h"
#include "Components/ActorComponent.h"
#include "MPatrolPathFollowerComponent.generated.h"

class AMPatrolPath;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBILEAI_API UMPatrolPathFollowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMPatrolPathFollowerComponent();

	// Methods
	static UMPatrolPathFollowerComponent* GetPatrolPathFollowerComp(const APawn* TargetPawn);
	FVector GetPatrolLocation();

	// Getters
	bool HasPatrolPath() const	{ return PatrolPath != nullptr; }
	AMPatrolPath* GetPatrolPath() const	{ return PatrolPath; }
	uint8 GetPatrolIndex() const	{ return CurrentPatrolIndex; }
	float GetPatrolToleranceDistance() const	{ return PatrolPath->GetPatrolToleranceDistance(); }
	

	// Data
protected:
	/** Patrol Path to Follow */
	UPROPERTY(EditInstanceOnly, Category=Gameplay)
	AMPatrolPath* PatrolPath;
	
	/** Should walk in reverse path? */
	UPROPERTY(EditInstanceOnly, Category=Gameplay)
	bool bReverse;

private:
	UPROPERTY()
	uint8 CurrentPatrolIndex;
};
