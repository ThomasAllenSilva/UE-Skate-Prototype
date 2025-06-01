// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkaterComponent.generated.h"

class ASkateCharacter;

/*
*
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class USkaterComponent final : public UActorComponent
{
	GENERATED_BODY()

public:
	USkaterComponent();

	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	void TryPlayPushForwardMontage();

	void PlayJumpMontage();

	bool IsAbleToPushForward() const;

	bool IsAbleToJump() const;

private:
	void OnNotifyPushForwardMontage();

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
