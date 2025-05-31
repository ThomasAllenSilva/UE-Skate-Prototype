// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SkatePlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class ASkateCharacter;
class UAnimMontage;
class UDataAsset_SkateControlSettings;

struct FInputActionValue;

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

	void Input_Turn(const FInputActionValue& InputValue);

	void Input_Slowdown();

	FVector GetTargetMovementDirection() const;

private:
	/* Movement */
	UPROPERTY(EditAnywhere)
	float CurrentAcceleration;

	/* Inputs */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> AccelerateInput;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> TurnInput;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SlowdownInput;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY()
	TObjectPtr<ASkateCharacter> SkaterCharacter;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataAsset_SkateControlSettings> SkateControlSettings;
};
