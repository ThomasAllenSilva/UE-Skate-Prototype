// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SkateCharacter.h"
#include "Components/SkaterComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/SkateMovementComponent.h"
#include "GameFramework/PlayerState.h"
#include "Blueprint/UserWidget.h"

ASkateCharacter::ASkateCharacter()
{
	SkaterComponent = CreateDefaultSubobject<USkaterComponent>("SkaterComponent");
}

UPointsSystemComponent* ASkateCharacter::GetPointsSystemComponent() const
{
	return PointsSystemComponent;
}

USkateMovementComponent* ASkateCharacter::GetSkateMovementComponent() const
{
	return SkateMovementComponent;
}

void ASkateCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	APlayerState* CurrentPlayerState = GetPlayerState<APlayerState>();

	IPointsSystemInterface* PointsSystemInterface = CastChecked<IPointsSystemInterface>(CurrentPlayerState);

	PointsSystemComponent = PointsSystemInterface->GetPointsSystemComponent();

	SkateMovementComponent = CastChecked<USkateMovementComponent>(GetCharacterMovement());

	check(PointsSystemComponent);
}

void ASkateCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(PointsWidget);

	UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), PointsWidget);

	WidgetInstance->AddToViewport();
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

void ASkateCharacter::Input_Accelerate()
{
	SkaterComponent->TryPlayPushForwardMontage();
}

void ASkateCharacter::Input_Turn(const FInputActionValue& InputValue)
{
	float TurnValue = InputValue.Get<float>();

	Cast<APlayerController>(GetController())->AddYawInput(TurnValue);
}

void ASkateCharacter::Input_Slowdown()
{
	SkateMovementComponent->SlowDown();
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
	FVector Direction = GetTargetMovementDirection();

	SkateMovementComponent->Push(Direction);
}

FVector ASkateCharacter::GetTargetMovementDirection() const
{
	float YawRotation = GetActorRotation().Yaw;

	const FRotator ControllerRotation = FRotator(0, YawRotation, 0);

	FVector Direction = FRotationMatrix(ControllerRotation).GetUnitAxis(EAxis::X);

	return Direction;
}
