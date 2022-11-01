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

DEFINE_LOG_CATEGORY(LogAI);


AMAIController::AMAIController()
{
	// Setup Sight Perception Config
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	SightConfig->SightRadius = 1'000.f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 500.f;
	SightConfig->PeripheralVisionAngleDegrees = 60.f;
	SightConfig->SetMaxAge(5.f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception"));
}

void AMAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->SetDominantSense(SightConfig->GetSenseImplementation());
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
			UE_LOG(LogAI, Warning, TEXT("Sight Deactivated"))
			break;
		}
	case EAIState::Guard:
		{
			GetPerceptionComponent()->SetSenseEnabled(SightConfig->GetSenseImplementation(), true);
			UE_LOG(LogAI, Warning, TEXT("Sight Activated"))
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
	UE_LOG(LogAI, Warning, TEXT("Pawn Seen"));

	if (AMPlayerCharacter* MPlayerCharacter = Cast<AMPlayerCharacter>(Actor))
	{
		Blackboard->SetValueAsObject("Player", MPlayerCharacter);
	
		if (AMGameModeBase* MGameMode = Cast<AMGameModeBase>(GetWorld()->GetAuthGameMode()))
			MGameMode->ReportPlayerDetected();
	}
}