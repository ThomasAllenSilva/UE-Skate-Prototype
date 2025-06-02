// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/PointsSystemInterface.h"
#include "SkateCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class USkaterComponent;
class UPointsSystemComponent;
class USkateMovementComponent;
struct FInputActionValue;

/*
* Main character class for this project
* Relies on a custom Skate Movement Component for physics and a Skater Component for animation handling
*/
UCLASS()
class ASkateCharacter final : public ACharacter, public IPointsSystemInterface
{
	GENERATED_BODY()

public:
	ASkateCharacter();

	//~PointsSystem Interface
	virtual UPointsSystemComponent* GetPointsSystemComponent() const;
	//~ End of PointsSystem Interface

	/* Returns the SkateMovementComponent used to control this character */
	USkateMovementComponent* GetSkateMovementComponent() const;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Apply an impulse towards the current movement direction */
	void PushForward();

protected:
	virtual void PossessedBy(AController* NewController) override;

private:
	/* Callback for when the accelerate input is triggered. Used for push the skate forward using montage */
	void Input_Accelerate();

	/* Callback for when the turn input is triggered. Used to rotate the control and guide the direction */
	void Input_Turn(const FInputActionValue& InputValue);

	/* Callback for when the slowdown input is triggered. Used to slowdown the skateboard */
	void Input_Slowdown();

	/* Callback for when the jump input is triggered. Used to set a pending jump for later execution */
	void Input_Jump();

	/* Returns the current direction that this character is moving at using the control rotation */
	FVector GetTargetMovementDirection() const;

private:

	/* Input used to push the skate forward */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> AccelerateInput;

	/* The input used to rotate the controller */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> TurnInput;

	/* The input used to slowdown the skateboard */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SlowdownInput;

	/* The input used to make the character jump */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpInput;

	/* The mapping context used to control this character */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	/* The skater component that manages animations and skate-specific actions */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkaterComponent> SkaterComponent;

	/* The points system component used by this actor */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPointsSystemComponent> PointsSystemComponent;

	/* The movement component used to control this character */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkateMovementComponent> SkateMovementComponent;
};
