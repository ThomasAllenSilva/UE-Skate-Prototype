// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SkatePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/SkateCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkaterComponent.h"
#include "Data/DataAsset_SkateControlSettings.h"

void ASkatePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SkaterCharacter = CastChecked<ASkateCharacter>(InPawn);
}

void ASkatePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(AccelerateInput, ETriggerEvent::Triggered, this, &ThisClass::Input_Accelerate);

	EnhancedInputComponent->BindAction(TurnInput, ETriggerEvent::Triggered, this, &ThisClass::Input_Turn);

	EnhancedInputComponent->BindAction(SlowdownInput, ETriggerEvent::Triggered, this, &ThisClass::Input_Slowdown);

	ULocalPlayer* LocalPlayer = GetLocalPlayer();

	if (auto* Subsys = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		Subsys->AddMappingContext(InputMappingContext, 0);
	}
}

void ASkatePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector Direction = GetTargetMovementDirection() * CurrentAcceleration;

	SkaterCharacter->AddMovementInput(Direction);

	CurrentAcceleration -= DeltaSeconds / SkateControlSettings->GetAccelerationDuration();

	float MinAcceleration = SkateControlSettings->GetMinAcceleration();

	if (CurrentAcceleration <= MinAcceleration)
	{
		CurrentAcceleration = MinAcceleration;
	}
}

void ASkatePlayerController::Input_Accelerate()
{
	if (CurrentAcceleration < SkateControlSettings->GetTargetAccelerationForImpulse()) 
	{
		USkaterComponent* SkaterComponent = SkaterCharacter->GetSkaterComponent();

		SkaterComponent->TryPlayPushForwardMontage();
	}
}

void ASkatePlayerController::Input_Turn(const FInputActionValue& InputValue)
{
	float TurnValue = InputValue.Get<float>();

	TurnValue *= SkateControlSettings->GetTurnRate();

	AddYawInput(TurnValue);
}

void ASkatePlayerController::Input_Slowdown()
{
	CurrentAcceleration = FApp::GetDeltaTime();

	float MinAcceleration = SkateControlSettings->GetMinAcceleration();

	if (CurrentAcceleration <= MinAcceleration)
	{
		CurrentAcceleration = MinAcceleration;
	}
}

void ASkatePlayerController::PushForward()
{
	CurrentAcceleration = 1;

	FVector Direction = GetTargetMovementDirection() * SkateControlSettings->GetPushImpulse();

	SkaterCharacter->GetCharacterMovement()->AddImpulse(Direction, true);
}

FVector ASkatePlayerController::GetTargetMovementDirection() const
{
	float YawRotation = GetControlRotation().Yaw;

	const FRotator ControllerRotation = FRotator(0, YawRotation, 0);

	FVector Direction = FRotationMatrix(ControllerRotation).GetUnitAxis(EAxis::X);

	return Direction;
}
