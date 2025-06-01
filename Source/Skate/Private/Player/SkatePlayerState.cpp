// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SkatePlayerState.h"
#include "Components/PointsSystemComponent.h"

ASkatePlayerState::ASkatePlayerState()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	PointsSystemComponent = CreateDefaultSubobject<UPointsSystemComponent>("PointsSystemComponent");
}

UPointsSystemComponent* ASkatePlayerState::GetPointsSystemComponent() const
{
	return PointsSystemComponent;
}
