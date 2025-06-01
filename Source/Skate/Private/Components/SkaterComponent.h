// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkaterComponent.generated.h"

class ASkateCharacter;

/*
* Handles movement-related animations and events for the owning skate character
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class USkaterComponent final : public UActorComponent
{
	GENERATED_BODY()

public:
	USkaterComponent();

	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	/* Checks whether the push montage can be played before executing it */
	void TryPlayPushForwardMontage();

	/* Plays the jump montage selected for this component */
	void PlayJumpMontage();

	/* Checks if the player can add a boost to the SkateBoard */
	bool IsAbleToPushForward() const;

	/* Checks if the player can jump */
	bool IsAbleToJump() const;

private:
	/* Callback received from the push forward montage event */
	void OnNotifyPushForwardMontage();

	/* Callback received from the jump montage event */
	void OnNotifyJumpMontage();

private:
	/*The montage to play when a new push is required */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> PushSkateForwardMontage;

	/*The montage to play when a new push is required */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> JumpMontage;

	/* The owning character of this component */
	UPROPERTY()
	TObjectPtr<ASkateCharacter> OwningCharacter;

	/* The anim instance used by the owning characater */
	UPROPERTY()
	TObjectPtr<UAnimInstance> OwningCharacterAnimInstance;
};
