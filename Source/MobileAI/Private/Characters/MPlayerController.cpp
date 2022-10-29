// Code made by Luccas Machado. Feel free to use it anyway you like!


#include "Characters/MPlayerController.h"

// Called on begin play
void AMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ActivateTouchInterface(MovementTouchInterface);
}
