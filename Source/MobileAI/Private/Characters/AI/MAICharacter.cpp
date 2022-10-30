// Code made by Luccas Machado. Feel free to use it anyway you like it!


#include "Characters/AI/MAICharacter.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMAICharacter::AMAICharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	// Character movement setup
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 270.f, 0.0f);
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	// TextRender setup
	TextRenderComp = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComp");
	TextRenderComp->SetupAttachment(GetMesh(), "headTextSocket");
	TextRenderComp->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TextRenderComp->WorldSize = 0.f;
	TextRenderComp->SetVisibility(false);

	// Sleep Display Setup
	DisplaySleepStruct.DisplayText = "Zz";
	DisplaySleepStruct.PlayRate = 1.f;
	DisplaySleepStruct.DisplayTime = 0.f;
	DisplaySleepStruct.bLoop = true;

	// Alert Display Setup
	DisplayAlertStruct.DisplayText = "!";
	DisplayAlertStruct.PlayRate = 4.f;
	DisplayAlertStruct.DisplayTime = 0.8f;
	DisplayAlertStruct.bLoop = false;
}

void AMAICharacter::SetAIState_Implementation(const EAIState NewState)
{
	AIState = NewState;
	OnStateChanged.Execute(AIState);

	switch (AIState)
	{
	case EAIState::Idle: case EAIState::Guard: default:
		{
			StopDisplayState();
			break;
		}
	case EAIState::Sleep:
		{
			DisplayState(DisplaySleepStruct);
			break;
		}
	case EAIState::Alert:
		{
			DisplayState(DisplayAlertStruct);
			break;
		}
	}
}

