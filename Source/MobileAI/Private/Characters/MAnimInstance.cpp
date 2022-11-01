// Code made by Luccas Machado. Feel free to use it anyway you like!


#include "Characters/MAnimInstance.h"
#include "Characters/MCharacterBase.h"
#include "GameFramework/PawnMovementComponent.h"


void UMAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (TryGetPawnOwner())
	{
		const AMCharacterBase* MyCharacter = Cast<AMCharacterBase>(TryGetPawnOwner());
		if (MyCharacter != nullptr)
		{
			bCrouching = MyCharacter->GetCrouching();
			WalkingSpeed = MyCharacter->GetMovementComponent()->Velocity.Size();
		}
	}
}
