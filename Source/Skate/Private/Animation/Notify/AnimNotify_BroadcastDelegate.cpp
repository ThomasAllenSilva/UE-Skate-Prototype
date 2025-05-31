// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_BroadcastDelegate.h"

void UAnimNotify_BroadcastDelegate::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnNotify.Broadcast();
}
