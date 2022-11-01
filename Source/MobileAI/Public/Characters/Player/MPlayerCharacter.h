// Code made by Luccas Machado. Feel free to use it anyway you like it!


#pragma once
#include "CoreMinimal.h"
#include "Characters/MCharacterBase.h"
#include "MPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAIPerceptionStimuliSourceComponent;
class UAISense;


UCLASS()
class MOBILEAI_API AMPlayerCharacter : public AMCharacterBase
{
	GENERATED_BODY()

public:
	AMPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	// Inputs
	void MoveForward(float Value);
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable)
	void Punch();
	void FireWeapon();
	void CrouchFlipFlop();
	void ConsumeItem();
	void Interact();

	// Components
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	UCameraComponent* ThirdPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Componets)
	UAIPerceptionStimuliSourceComponent* AIStimuliComp;


	// Movement
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	float BaseWalkSpeed;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	float CrouchedWalkSpeed;;
	
	
	// Getters	
public:
	/** Get Camera Boom */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Get Third Person Camera */
	FORCEINLINE UCameraComponent* GetThirdPersonCamera() const { return ThirdPersonCamera; }
};
