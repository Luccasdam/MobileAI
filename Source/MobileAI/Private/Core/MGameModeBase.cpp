// Code made by Luccas Machado. Feel free to use it anyway you like it!


#include "Core/MGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void AMGameModeBase::SetGameOver(bool bMissionSucceeded)
{
	if (bGameOver == false)
	{
		bGameOver = true;
		DisplayGameOverScreen(bMissionSucceeded);
	}
}

void AMGameModeBase::ReportPlayerDetected()
{
	if (bGameOver)
		return;
	
	switch (PlayerDetectedHandleMethod)
	{
	case EPlayerDetectedHandleMethod::RestartLevel: default:
		{
			SetGameOver(false);
			
			FTimerHandle TimerHandle_RestartLevel;
			GetWorldTimerManager().SetTimer(TimerHandle_RestartLevel, this, &AMGameModeBase::ReloadLevel, ReportDelay);
			break;
		}
	}
}

void AMGameModeBase::ReloadLevel() const
{
	UGameplayStatics::OpenLevel(this, *UGameplayStatics::GetCurrentLevelName(this));
}
