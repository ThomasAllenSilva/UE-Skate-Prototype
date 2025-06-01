// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SkateCharacter.h"
#include "Components/SkaterComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Data/DataAsset_SkateControlSettings.h"
#include "GameFramework/CharacterMovementComponent.h"

ASkateCharacter::ASkateCharacter()
{
	SkaterComponent = CreateDefaultSubobject<USkaterComponent>("SkaterComponent");
}

void ASkateCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (IsLocallyControlled() == false)
	{
		return;
	}

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(AccelerateInput, ETriggerEvent::Triggered, this, &ThisClass::Input_Accelerate);

	EnhancedInputComponent->BindAction(TurnInput, ETriggerEvent::Triggered, this, &ThisClass::Input_Turn);

	EnhancedInputComponent->BindAction(SlowdownInput, ETriggerEvent::Triggered, this, &ThisClass::Input_Slowdown);

	EnhancedInputComponent->BindAction(JumpInput, ETriggerEvent::Triggered, this, &ThisClass::Input_Jump);

	ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void ASkateCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector Direction = GetTargetMovementDirection() * CurrentAcceleration;

	AddMovementInput(Direction);

	CurrentAcceleration -= DeltaSeconds / SkateControlSettings->GetAccelerationDuration();

	float MinAcceleration = SkateControlSettings->GetMinAcceleration();

	if (CurrentAcceleration <= MinAcceleration)
	{
		CurrentAcceleration = MinAcceleration;
	}
}

USkaterComponent* ASkateCharacter::GetSkaterComponent()
{
	return SkaterComponent;
}

void ASkateCharacter::Input_Accelerate()
{
	if (CurrentAcceleration < SkateControlSettings->GetTargetAccelerationForImpulse())
	{
		SkaterComponent->TryPlayPushForwardMontage();
	}
}

void ASkateCharacter::Input_Turn(const FInputActionValue& InputValue)
{
	float TurnValue = InputValue.Get<float>();

	TurnValue *= SkateControlSettings->GetTurnRate();

	Cast<APlayerController>(GetController())->AddYawInput(TurnValue);
}

void ASkateCharacter::Input_Slowdown()
{
	CurrentAcceleration = FApp::GetDeltaTime();

	float MinAcceleration = SkateControlSettings->GetMinAcceleration();

	if (CurrentAcceleration <= MinAcceleration)
	{
		CurrentAcceleration = MinAcceleration;
	}
}

void ASkateCharacter::Input_Jump()
{
	if (SkaterComponent->IsAbleToJump())
	{
		SkaterComponent->PlayJumpMontage();
	}
}

void ASkateCharacter::PushForward()
{
	CurrentAcceleration = 1;

	FVector Direction = GetTargetMovementDirection() * SkateControlSettings->GetPushImpulse();

	GetCharacterMovement()->AddImpulse(Direction, true);
}

FVector ASkateCharacter::GetTargetMovementDirection() const
{
	float YawRotation = GetActorRotation().Yaw;

	const FRotator ControllerRotation = FRotator(0, YawRotation, 0);

	FVector Direction = FRotationMatrix(ControllerRotation).GetUnitAxis(EAxis::X);

	return Direction;
}