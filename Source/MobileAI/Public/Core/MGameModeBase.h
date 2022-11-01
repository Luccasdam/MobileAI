// Code made by Luccas Machado. Feel free to use it anyway you like it!


#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MGameModeBase.generated.h"


UENUM(BlueprintType)
enum class EPlayerDetectedHandleMethod : uint8
{
	GameOver
};


/**
 * 
 */
UCLASS()
class MOBILEAI_API AMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	// Methods
public:
	// TODO: This should be made inside an AI Manager Class. Making here just for simplicity.
	void ReportPlayerDetected();
	
	UFUNCTION(BlueprintCallable)
	void SetGameOver(bool bMissionSucceeded);

	UFUNCTION(BlueprintImplementableEvent)
	void DisplayGameOverScreen(bool bMissionSucceeded);

	UFUNCTION(BlueprintCallable)
	void RetryCurrentLevel();

	UFUNCTION(BlueprintCallable)
	void OpenNextLevel();

	// Data
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	EPlayerDetectedHandleMethod PlayerDetectedHandleMethod;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Gameplay)
	float ReportDelay = 3.0f;

private:
	UPROPERTY(BlueprintReadOnly, Category=Gameplay, meta=(AllowPrivateAccess))
	bool bGameOver = false;

	// Temp
protected:
	uint8 GetNextLevelIndex();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Temp)
	TArray<FString> LevelNameList;
};
