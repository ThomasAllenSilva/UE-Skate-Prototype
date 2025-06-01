// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/PointsSystemInterface.h"
#include "SkateCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class ASkateCharacter;
class UAnimMontage;
class UDataAsset_SkateControlSettings;
class USkaterComponent;
struct FInputActionValue;
class UPointsSystemComponent;

UCLASS()
class ASkateCharacter final : public ACharacter, public IPointsSystemInterface
{
	GENERATED_BODY()

public:
	ASkateCharacter();


	//~PointsSystem Interface
	virtual UPointsSystemComponent* GetPointsSystemComponent() const;
	//~ End of PointsSystem Interface

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds);
	USkaterComponent* GetSkaterComponent();

	void PushForward();

protected:
	virtual void PossessedBy(AController* NewController) override;

private:
	void Input_Accelerate();

	void Input_Turn(const FInputActionValue& InputValue);

	void Input_Slowdown();

	void Input_Jump();

	FVector GetTargetMovementDirection() const;
private:
	UFUNCTION(Exec)
	void Debug_Add100Points();

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkaterComponent> SkaterComponent;

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
	TObjectPtr<UInputAction> JumpInput;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataAsset_SkateControlSettings> SkateControlSettings;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPointsSystemComponent> PointsSystemComponent;
};
