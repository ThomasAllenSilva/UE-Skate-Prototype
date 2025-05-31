// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkaterComponent.generated.h"

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

	bool IsAbleToPushForward() const;

private:
	void OnNotifyPushForwardMontage();

private:
	/*The montage to play when a new push is required */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> PushSkateForwardMontage;

	/* The owning character of this component */
	UPROPERTY()
	TObjectPtr<ACharacter> OwningCharacter;

	/* The anim instance used by the owning characater */
	UPROPERTY()
	TObjectPtr<UAnimInstance> OwningCharacterAnimInstance;
};
