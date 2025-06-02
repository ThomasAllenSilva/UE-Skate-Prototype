// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SkateMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

void USkateMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	if (IsCharacterGrounded())
	{
		HandleSkateSlippery();
	}

	Velocity += GetDesiredGravityForce() * FVector::DownVector * deltaTime;

	TryHandleJump();

	CalcVelocity(deltaTime, SkateGroundFriction, true, GetMaxBrakingDeceleration());

	FQuat DesiredRotation = GetDesiredRotation(deltaTime);

	FVector Delta = Velocity * deltaTime;

	FVector OldLocation = UpdatedComponent->GetComponentLocation();

	FHitResult Hit;

	SafeMoveUpdatedComponent(Delta, DesiredRotation, true, Hit);

	if (Hit.bBlockingHit)
	{
		HandleImpact(Hit, deltaTime, Delta);

		SlideAlongSurface(Delta, (1.0f - Hit.Time), Hit.Normal, Hit, false);
	}

	FVector NewLocation = UpdatedComponent->GetComponentLocation();

	Velocity = (NewLocation - OldLocation) / deltaTime;
}

void USkateMovementComponent::Jump()
{
	bWantsToJump = true;
}

void USkateMovementComponent::Push(FVector Direction)
{
	FVector Impulse = Direction * PushImpulse;

	AddImpulse(Impulse, true);
}

float USkateMovementComponent::GetDesiredGravityForce() const
{
	if (IsCharacterGrounded())
	{
		return GroundedGravityForce;
	}
	else
	{
		return FlyingGravityForce;
	}
}

FQuat USkateMovementComponent::GetDesiredRotation(float deltaTime) const
{
	const FRotator ComponentRotation = UpdatedComponent->GetComponentRotation();

	FQuat DesiredRotation = ComponentRotation.Quaternion();

	if (IsCharacterGrounded())
	{
		FRotator AlignedSurfaceRotation = FRotationMatrix::MakeFromZX(GetCurrentSurfaceNormal(), UpdatedComponent->GetForwardVector()).Rotator();

		DesiredRotation = FMath::RInterpTo(ComponentRotation, AlignedSurfaceRotation, deltaTime, RotationSmoothingInterpSpeed).Quaternion();
	}

	else if (Velocity.IsNearlyZero() == false)
	{
		FRotator DirectionRotation = Velocity.ToOrientationRotator();

		DirectionRotation.Pitch = FMath::Clamp(DirectionRotation.Pitch, -MaxAirPitch, MaxAirPitch);

		DesiredRotation = FMath::RInterpTo(ComponentRotation, DirectionRotation, deltaTime, RotationSmoothingInterpSpeed).Quaternion();
	}

	return DesiredRotation;
}

bool USkateMovementComponent::IsCharacterGrounded() const
{
	FHitResult HitResult;

	const UCapsuleComponent* CharacterCapsule = CharacterOwner->GetCapsuleComponent();

	const FVector ForwardVector = CharacterOwner->GetActorForwardVector();

	const FVector UpVector = CharacterOwner->GetActorUpVector();

	const FVector StartLocation = CharacterCapsule->GetComponentLocation();

	const FVector EndLocation = StartLocation - (UpVector * CharacterCapsule->GetScaledCapsuleHalfHeight() * 1.5f);

	const bool bIsGrounded = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);

	return bIsGrounded;
}

void USkateMovementComponent::HandleSkateSlippery()
{
	FVector RightVector = UpdatedComponent->GetRightVector();

	float SidewaysSpeed = FVector::DotProduct(Velocity, RightVector);

	Velocity -= RightVector * SidewaysSpeed;

	Velocity += RightVector * (SidewaysSpeed * SideSlipFactor);
}

void USkateMovementComponent::TryHandleJump()
{
	if (bWantsToJump && IsCharacterGrounded())
	{
		Velocity += CharacterOwner->GetActorUpVector() * JumpImpulse;

		bWantsToJump = false;
	}
}

FVector USkateMovementComponent::GetCurrentSurfaceNormal() const
{
	FHitResult HitResult;

	const UCapsuleComponent* CharacterCapsule = CharacterOwner->GetCapsuleComponent();

	const FVector ForwardVector = CharacterOwner->GetActorForwardVector();

	const FVector UpVector = CharacterOwner->GetActorUpVector();

	const FVector StartLocation = CharacterCapsule->GetComponentLocation();

	const FVector EndLocation = StartLocation - (UpVector * CharacterCapsule->GetScaledCapsuleHalfHeight() * 2.5f);

	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);

	return HitResult.Normal;
}

void USkateMovementComponent::SlowDown()
{
	if (IsCharacterGrounded() == false)
	{
		return;
	}

	FVector CharacterForward = UpdatedComponent->GetForwardVector();

	float CurrentForwardSpeed = FVector::DotProduct(Velocity, CharacterForward);

	if (CurrentForwardSpeed > 0.0f)
	{
		float ReducedForwardSpeed = FMath::Max(CurrentForwardSpeed - SlowDownAcceleration, 0.0f);

		FVector CurrentForwardVelocity = CharacterForward * CurrentForwardSpeed;

		FVector SidesVelocity = Velocity - CurrentForwardVelocity; //here we're just keeping the sides velocity in case we're slipping 

		Velocity = SidesVelocity + (CharacterForward * ReducedForwardSpeed);
	}
}
