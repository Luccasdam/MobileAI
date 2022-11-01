// Code made by Luccas Machado. Feel free to use it anyway you like it!


#include "Characters/AI/MAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/AI/MAICharacter.h"
#include "Characters/Player/MPlayerCharacter.h"
#include "Core/MGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "MobileAI/MobileAI.h"
#include "Perception/AISenseConfig_Hearing.h"

DEFINE_LOG_CATEGORY(LogAI);

#define STIMULI_TYPE_NAME_SIGHT "Default__AISense_Sight"
#define STIMULI_TYPE_NAME_HEARING "Default__AISense_Hearing"


AMAIController::AMAIController()
{
	// Setup Sight Perception Config
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	SightConfig->SightRadius = 500.f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 250.f;
	SightConfig->PeripheralVisionAngleDegrees = 60.f;
	SightConfig->SetMaxAge(5.f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// Setup Hearing Perception Config
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>("HearingConfig");
	HearingConfig->HearingRange = 500.f;
	HearingConfig->bUseLoSHearing = false;
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	UAIPerceptionComponent* PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception");
	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->ConfigureSense(*HearingConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
	SetPerceptionComponent(*PerceptionComp);
}

void AMAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMAIController::OnTargetPerceptionUpdated);
}

void AMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AMAICharacter* MAICharacter = Cast<AMAICharacter>(InPawn);
	if (MAICharacter == nullptr)
		return;
		
	MAICharacter->OnStateChanged.BindUFunction(this, "OnCharacterStateChanged");
	
	if (ensure(MAICharacter->GetBT() != nullptr))
	{
		RunBehaviorTree(MAICharacter->GetBT());
		Blackboard->SetValueAsVector("SpawnLocation", MAICharacter->GetActorLocation());
		Blackboard->SetValueAsRotator("SpawnRotation", MAICharacter->GetActorRotation());
	}
}

void AMAIController::OnCharacterStateChanged(const EAIState& NewState)
{
	switch (NewState)
	{
	case EAIState::Idle:
		{
			break;
		}
	case EAIState::Sleep:
		{
			GetPerceptionComponent()->SetSenseEnabled(SightConfig->GetSenseImplementation(), false);
			UE_LOG(LogAI, Log, TEXT("Sight Deactivated"))
			break;
		}
	case EAIState::Guard:
		{
			GetPerceptionComponent()->SetSenseEnabled(SightConfig->GetSenseImplementation(), true);
			UE_LOG(LogAI, Log, TEXT("Sight Activated"))
			break;
		}
	case EAIState::Suspicious:
		{
			UE_LOG(LogAI, Warning, TEXT("Suspicious State doesn't change state inside AI Controller"))
			break;
		}
	case EAIState::Investigating:
		{
			Blackboard->SetValueAsBool("bInvestigating", true);
			break;
		}
	case EAIState::Alert:
		{
			UE_LOG(LogAI, Warning, TEXT("Alert State doesn't change state inside AI Controller"))
			break;
		}
	default:
		{
			UE_LOG(LogAI, Warning, TEXT("There's no state set"))
		}
	}
}

void AMAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.Type.Name == STIMULI_TYPE_NAME_SIGHT)
	{
		UE_LOG(LogAIPerception, Log, TEXT("AI Target Perception Updated: Sight Sense"))
		if (AMPlayerCharacter* MPlayerCharacter = Cast<AMPlayerCharacter>(Actor))
		{
			Blackboard->SetValueAsObject("Player", MPlayerCharacter);
		
			if (AMGameModeBase* MGameMode = Cast<AMGameModeBase>(GetWorld()->GetAuthGameMode()))
				MGameMode->ReportPlayerDetected();
		}
	}

	if (Stimulus.Type.Name == STIMULI_TYPE_NAME_HEARING)
	{
		UE_LOG(LogAIPerception, Log, TEXT("AI Target Perception Updated: Hearing Sense"))

		// Received a new suspicious info
		Blackboard->SetValueAsBool("bSuspicious", true);
		
		// Stop investigation when received a new info
		Blackboard->SetValueAsBool("bInvestigating", false);
		
		// TODO: Make a better way of getting the NoiseLocation
		Blackboard->SetValueAsVector("NoiseLocation", Actor->GetActorLocation());
	}
}