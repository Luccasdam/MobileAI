// Code made by Luccas Machado. Feel free to use it anyway you like it!


#include "Core/MGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MobileAI/MobileAI.h"


void AMGameModeBase::ReportPlayerDetected()
{
	if (bGameOver)
		return;
	
	switch (PlayerDetectedHandleMethod)
	{
	case EPlayerDetectedHandleMethod::GameOver: default:
		{
			SetGameOver(false);
			break;
		}
	}
}

void AMGameModeBase::SetGameOver(bool bMissionSucceeded)
{
	if (bGameOver == false)
	{
		bGameOver = true;
		DisplayGameOverScreen(bMissionSucceeded);
		
		FTimerHandle TimerHandle_OpenLevel;
		if (bMissionSucceeded)
			GetWorldTimerManager().SetTimer(TimerHandle_OpenLevel, this, &AMGameModeBase::OpenNextLevel, ReportDelay);
		else
			GetWorldTimerManager().SetTimer(TimerHandle_OpenLevel, this, &AMGameModeBase::RetryCurrentLevel, ReportDelay);
	}
}



// TODO: Not using best practices to open levels. This code is only for quick testing purposes
void AMGameModeBase::RetryCurrentLevel()
{
	UGameplayStatics::OpenLevel(this, *UGameplayStatics::GetCurrentLevelName(this));
}

void AMGameModeBase::OpenNextLevel()
{
	UGameplayStatics::OpenLevel(this, *LevelNameList[GetNextLevelIndex()]);
}

uint8 AMGameModeBase::GetNextLevelIndex()
{
	for (uint8 Idx=0; Idx < LevelNameList.Num(); ++Idx)
		if (UGameplayStatics::GetCurrentLevelName(this) == LevelNameList[Idx])
			return Idx+1 == LevelNameList.Num() ? 0 : Idx+1;

	// Case Current Level Isn't in the list
	UE_LOG(LogMobileAI, Warning, TEXT("Current Level name not found inside LevelNameList"))
	return 0;
}

