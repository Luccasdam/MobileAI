// Code made by Luccas Machado. Feel free to use it anyway you like!


#include "Characters/Player/MPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"


AMPlayerCharacter::AMPlayerCharacter()
	: BaseWalkSpeed(600.f)
	, CrouchedWalkSpeed(300.f)
{
	PrimaryActorTick.bCanEverTick = true;

	// Don't use controller rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Character movement setup
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// CameraBoom setup
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	// Camera setup
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera");
	ThirdPersonCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	ThirdPersonCamera->bUsePawnControlRotation = false;

	// AI Perception Stimuli
	AIStimuliComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("AIStimuli");
	AIStimuliComp->RegisterForSense(AISenseClass);
}

void AMPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Punch", IE_Pressed, this, &AMPlayerCharacter::Punch);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMPlayerCharacter::FireWeapon);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMPlayerCharacter::CrouchFlipFlop);
	PlayerInputComponent->BindAction("Consume", IE_Pressed, this, &AMPlayerCharacter::ConsumeItem);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMPlayerCharacter::Interact);
}


void AMPlayerCharacter::MoveForward(float Value)
{
	if (Controller && Value)
	{
		const FVector Direction = FRotator(0.f, ThirdPersonCamera->GetComponentRotation().Yaw, 0.f).Vector();
		AddMovementInput(Direction, Value);
	}
}

void AMPlayerCharacter::MoveRight(float Value)
{
	if (Controller && Value)
	{
		const FVector Direction = FQuatRotationMatrix(ThirdPersonCamera->GetComponentQuat()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMPlayerCharacter::Punch()
{
}

void AMPlayerCharacter::FireWeapon()
{
}

void AMPlayerCharacter::CrouchFlipFlop()
{
	bCrouching = !bCrouching;
	GetCharacterMovement()->MaxWalkSpeed = bCrouching ? CrouchedWalkSpeed : BaseWalkSpeed;
}

void AMPlayerCharacter::ConsumeItem()
{
}

void AMPlayerCharacter::Interact()
{
}
