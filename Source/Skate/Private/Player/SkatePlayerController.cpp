// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SkatePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/SkateCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void ASkatePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector Direction = FVector(CurrentAcceleration, 0, 0);

	SkateCharacter->AddMovementInput(Direction);

	CurrentAcceleration -= DeltaSeconds / 4;
}

void ASkatePlayerController::PushForward()
{
	CurrentAcceleration = 1;

	FVector Direction = FVector(1000, 0, 0);

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

	EnhancedInputComponent->BindAction(Accelerate, ETriggerEvent::Triggered, this, &ThisClass::Input_Accelerate);

	ULocalPlayer* LocalPlayer = GetLocalPlayer();

	if (auto* Subsys = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		Subsys->AddMappingContext(InputMappingContext, 0);
	}
}

void ASkatePlayerController::Input_Accelerate()
{
	if (CurrentAcceleration < 0.4f) //min acceleration
	{
		//play montage 
		//call anim notify
		//call push forward method
	}
}
