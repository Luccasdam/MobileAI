// Code made by Luccas Machado. Feel free to use it anyway you like!


#include "Characters/Player/MPlayerController.h"


void AMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ActivateTouchInterface(MovementTouchInterface);
}
