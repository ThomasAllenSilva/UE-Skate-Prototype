// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SkaterComponent.h"
#include "Animation/Notify/AnimNotify_BroadcastDelegate.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/SkateCharacter.h"

USkaterComponent::USkaterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
}

void USkaterComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningCharacter = CastChecked<ASkateCharacter>(GetOwner());

	if (OwningCharacter->IsLocallyControlled() == false)
	{
		return;
	}

	check(PushSkateForwardMontage);

	OwningCharacterAnimInstance = OwningCharacter->GetMesh()->GetAnimInstance();

	for (const FAnimNotifyEvent& NotifyEvent : PushSkateForwardMontage->Notifies)
	{
		if (UAnimNotify_BroadcastDelegate* DelegateNotify = Cast<UAnimNotify_BroadcastDelegate>(NotifyEvent.Notify))
		{
			DelegateNotify->OnNotify.AddUObject(this, &ThisClass::OnNotifyPushForwardMontage);
		}
	}


	for (const FAnimNotifyEvent& NotifyEvent : JumpMontage->Notifies)
	{
		if (UAnimNotify_BroadcastDelegate* DelegateNotify = Cast<UAnimNotify_BroadcastDelegate>(NotifyEvent.Notify))
		{
			DelegateNotify->OnNotify.AddUObject(this, &ThisClass::OnNotifyJumpMontage);
		}
	}
}

void USkaterComponent::BeginDestroy()
{
	Super::BeginDestroy();

	if (PushSkateForwardMontage == nullptr) //this is required because of the CDO
	{
		return;
	}

	for (const FAnimNotifyEvent& NotifyEvent : PushSkateForwardMontage->Notifies)
	{
		if (UAnimNotify_BroadcastDelegate* DelegateNotify = Cast<UAnimNotify_BroadcastDelegate>(NotifyEvent.Notify))
		{
			DelegateNotify->OnNotify.RemoveAll(this);
		}
	}

	for (const FAnimNotifyEvent& NotifyEvent : JumpMontage->Notifies)
	{
		if (UAnimNotify_BroadcastDelegate* DelegateNotify = Cast<UAnimNotify_BroadcastDelegate>(NotifyEvent.Notify))
		{
			DelegateNotify->OnNotify.RemoveAll(this);
		}
	}
}

void USkaterComponent::TryPlayPushForwardMontage()
{
	if (IsAbleToPushForward())
	{
		OwningCharacterAnimInstance->Montage_Play(PushSkateForwardMontage);
	}
}

void USkaterComponent::PlayJumpMontage()
{
	OwningCharacterAnimInstance->Montage_Play(JumpMontage);
}

bool USkaterComponent::IsAbleToPushForward() const
{
	check(OwningCharacterAnimInstance);

	bool bIsPlayingPushMontage = OwningCharacterAnimInstance->Montage_IsPlaying(PushSkateForwardMontage);

	bool bIsPlayingJumpMontage = OwningCharacterAnimInstance->Montage_IsPlaying(JumpMontage);

	bool bIsFalling = OwningCharacter->GetMovementComponent()->IsFalling();

	bool bIsAbleToPushForward = (bIsPlayingPushMontage == false && bIsFalling == false && bIsPlayingJumpMontage == false);

	return bIsAbleToPushForward;
}

bool USkaterComponent::IsAbleToJump() const
{
	bool bIsPlayingJumpMontage = OwningCharacterAnimInstance->Montage_IsPlaying(JumpMontage);

	bool bIsFalling = OwningCharacter->GetMovementComponent()->IsFalling();

	bool bIsAbleToJump = (bIsPlayingJumpMontage == false && bIsFalling == false);

	return bIsAbleToJump;
}

void USkaterComponent::OnNotifyPushForwardMontage()
{
	OwningCharacter->PushForward();
}

void USkaterComponent::OnNotifyJumpMontage()
{
	OwningCharacter->Jump();
}
