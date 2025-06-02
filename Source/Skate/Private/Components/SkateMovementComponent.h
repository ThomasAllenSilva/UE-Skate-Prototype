// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SkateMovementComponent.generated.h"

/**
 * Custom movement component used to move the character simulating a skateboard control
 */
UCLASS()
class USkateMovementComponent final : public UCharacterMovementComponent
{
	GENERATED_BODY()
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;

public:
	/* Set a pending jump to be executed in the next update */
	void Jump();

	/* Adds an impulse torwards the direction modifying the velocity, acting as a push */
	void Push(FVector Direction);

	/* Reduces forward speed while maintaining side speed */
	void SlowDown();

	/* Returns whether or not the character is on the ground surface */
	bool IsCharacterGrounded() const;

private:
	/* Returns the desired gravity we should apply based on whether the character is grounded or flying */
	float GetDesiredGravityForce() const;

	/* Returns the desired rotation based on whether the character is grounded or flying */
	FQuat GetDesiredRotation(float deltaTime) const;

	/* Applies sideways friction to reduce sliding */
	void HandleSkateSlippery();

	/* Attempts to jump checking if it was requested before executing it */
	void TryHandleJump();

	/* Returns the normal of the current surface the character is standing on */
	FVector GetCurrentSurfaceNormal() const;

private:
	/* The gravity force applied when the character is grounded */
	UPROPERTY(EditDefaultsOnly, Category = "Skate Settings")
	float GroundedGravityForce;

	/* The gravity force applied when the character is flying (not grounded) */
	UPROPERTY(EditDefaultsOnly, Category = "Skate Settings")
	float FlyingGravityForce;

	/* The impulse to apply when executing the jump */
	UPROPERTY(EditDefaultsOnly, Category = "Skate Settings")
	float JumpImpulse;

	/* The impulse to apply when pushing the skate */
	UPROPERTY(EditDefaultsOnly, Category = "Skate Settings")
	float PushImpulse;

	/* The friction applied to the skate velocity when grounded */
	UPROPERTY(EditDefaultsOnly, Category = "Skate Settings")
	float SkateGroundFriction;

	/* The acceleration that the SkateBoard speed is reduced when slowing down */
	UPROPERTY(EditDefaultsOnly, Category = "Skate Settings")
	float SlowDownAcceleration;

	/* Defines how quickly the character rotates to align with the floor (grounded) or movement direction (flying). */
	UPROPERTY(EditDefaultsOnly, Category = "Skate Settings")
	float RotationSmoothingInterpSpeed;

	/* Maximum angle the character can lean forward or backward while in the air */
	UPROPERTY(EditDefaultsOnly, Category = "Skate Settings")
	float MaxAirPitch;

	/* Defines how much sideways velocity is preserved when turning; 0 = no slip, 1 = full slip */
	UPROPERTY(EditDefaultsOnly, Category = "Skate Settings")
	float SideSlipFactor;

	/* Whether or not we should apply a jump impulse to the character */
	UPROPERTY()
	bool bWantsToJump;
};
