// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SkatePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/SkateCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/Notify/AnimNotify_BroadcastDelegate.h"
#include "Data/DataAsset_SkateControlSettings.h"

void ASkatePlayerController::BeginPlay()
{
	Super::BeginPlay();

	for (const FAnimNotifyEvent& NotifyEvent : PushSkateForwardMontage->Notifies)
	{
		if (UAnimNotify_BroadcastDelegate* DelegateNotify = Cast<UAnimNotify_BroadcastDelegate>(NotifyEvent.Notify))
		{
			DelegateNotify->OnNotify.AddUObject(this, &ThisClass::OnNotifyPushForwardMontage);
		}
	}
}

void ASkatePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector Direction = GetTargetMovementDirection() * CurrentAcceleration;

	SkateCharacter->AddMovementInput(Direction);

	CurrentAcceleration -= DeltaSeconds / SkateControlSettings->GetAccelerationDuration();

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

	SkateCharacter->GetCharacterMovement()->AddImpulse(Direction, true);
}

void ASkatePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SkateCharacter = CastChecked<ASkateCharacter>(InPawn);
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

void ASkatePlayerController::Input_Accelerate()
{
	//TODO: MOVE THIS LOGIC TO A COMPONENT
	if (CurrentAcceleration < SkateControlSettings->GetTargetAccelerationForImpulse()) //min acceleration
	{
		UAnimInstance* AnimInstance = SkateCharacter->GetMesh()->GetAnimInstance();

		check(AnimInstance);

		if (AnimInstance->Montage_IsPlaying(PushSkateForwardMontage) == false)
		{
			AnimInstance->Montage_Play(PushSkateForwardMontage);
		}
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

void ASkatePlayerController::OnNotifyPushForwardMontage()
{
	PushForward();
}

FVector ASkatePlayerController::GetTargetMovementDirection()
{
	float YawRotation = GetControlRotation().Yaw;

	const FRotator ControllerRotation = FRotator(0, YawRotation, 0);

	FVector Direction = FRotationMatrix(ControllerRotation).GetUnitAxis(EAxis::X);

	return Direction;
}
