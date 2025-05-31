// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_SkateControlSettings.generated.h"

/**
 * Settings used to control the skate
 */
UCLASS()
class UDataAsset_SkateControlSettings final : public UDataAsset
{
	GENERATED_BODY()
	
public:
	float GetPushImpulse() const;

	float GetTargetAccelerationForImpulse() const;

	float GetMinAcceleration() const;

	float GetAccelerationDuration() const;

	float GetTurnRate() const;

private:
	/* The impulse to be applied when pushing the skate forward */
	UPROPERTY(EditDefaultsOnly)
	float PushImpulse;

	/* The target value that the controller will wait to reach before applying a new impulse. Note: It must be greater than 'MinAcceleration' in order to work */
	UPROPERTY(EditDefaultsOnly)
	float TargetAccelerationForImpulse;

	/* The min value that should be applied to the character acceleration */
	UPROPERTY(EditDefaultsOnly)
	float MinAcceleration;

	/* The amount of time that an impulse should last before applying a new one */
	UPROPERTY(EditDefaultsOnly)
	float AccelerationDuration;

	/* The rotation rate applied to the controller */
	UPROPERTY(EditDefaultsOnly)
	float TurnRate;
};
