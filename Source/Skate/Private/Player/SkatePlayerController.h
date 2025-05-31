// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SkatePlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class ASkateCharacter;


/**
 * 
 */
UCLASS()
class ASkatePlayerController final : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds);

	void PushForward();

protected:
	virtual void OnPossess(APawn* InPawn);

	virtual void SetupInputComponent() override;

private:
	void Input_Accelerate();

private:
	/* Movement */
	UPROPERTY(EditAnywhere)
	float CurrentAcceleration;

	/* Inputs */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Accelerate;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> TurnLeft;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> TurnRight;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SlowdownInput;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY()
	TObjectPtr<ASkateCharacter> SkateCharacter;
};
