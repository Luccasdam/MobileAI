// Code made by Luccas Machado. Feel free to use it anyway you like it!


#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "MAICharacter.h"
#include "Perception/AIPerceptionTypes.h"
#include "MAIController.generated.h"

class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;


/**
 * 
 */
UCLASS()
class MOBILEAI_API AMAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMAIController();
	virtual void PostInitializeComponents() override;

protected:	
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
    void OnCharacterStateChanged(const EAIState& NewState);
	
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);


protected:
	UPROPERTY(EditDefaultsOnly, Category=AI)
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditDefaultsOnly, Category=AI)
	UAISenseConfig_Hearing* HearingConfig;
};
