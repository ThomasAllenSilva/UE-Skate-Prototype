// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_BroadcastDelegate.generated.h"

DECLARE_MULTICAST_DELEGATE(FNotifySignature)

/**
 * Used to broadcast events to C++ functions from an animation
 */
UCLASS()
class UAnimNotify_BroadcastDelegate final : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	/* Delegate used to notify C++ listeners when the notify has been called on the animation */
	FNotifySignature OnNotify;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
};
