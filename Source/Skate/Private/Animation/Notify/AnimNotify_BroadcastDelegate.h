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
class UAnimNotify_BroadcastDelegate : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FNotifySignature OnNotify;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
};
