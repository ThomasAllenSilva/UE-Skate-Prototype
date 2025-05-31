// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SkaterComponent.h"
#include "Animation/Notify/AnimNotify_BroadcastDelegate.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/SkatePlayerController.h"

USkaterComponent::USkaterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
}

void USkaterComponent::BeginPlay()
{
	Super::BeginPlay();

	check(PushSkateForwardMontage);

	OwningCharacter = CastChecked<ACharacter>(GetOwner());

	OwningCharacterAnimInstance = OwningCharacter->GetMesh()->GetAnimInstance();

	for (const FAnimNotifyEvent& NotifyEvent : PushSkateForwardMontage->Notifies)
	{
		if (UAnimNotify_BroadcastDelegate* DelegateNotify = Cast<UAnimNotify_BroadcastDelegate>(NotifyEvent.Notify))
		{
			DelegateNotify->OnNotify.AddUObject(this, &ThisClass::OnNotifyPushForwardMontage);
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
}

void USkaterComponent::TryPlayPushForwardMontage()
{
	if (IsAbleToPushForward())
	{
		OwningCharacterAnimInstance->Montage_Play(PushSkateForwardMontage);
	}
}

bool USkaterComponent::IsAbleToPushForward() const
{
	check(OwningCharacterAnimInstance);

	bool bIsPlayingPushMontage = OwningCharacterAnimInstance->Montage_IsPlaying(PushSkateForwardMontage);

	bool bIsFalling = OwningCharacter->GetMovementComponent()->IsFalling();

	bool bIsAbleToPushForward = (bIsPlayingPushMontage == false && bIsFalling == false);

	return bIsAbleToPushForward;
}

void USkaterComponent::OnNotifyPushForwardMontage()
{
	ASkatePlayerController* SkatePlayerController = CastChecked<ASkatePlayerController>(OwningCharacter->GetController());

	SkatePlayerController->PushForward();
}
