// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SkatePlayerState.h"
#include "Components/PointsSystemComponent.h"

ASkatePlayerState::ASkatePlayerState()
{
	PointsSystemComponent = CreateDefaultSubobject<UPointsSystemComponent>("PointsSystemComponent");
}

UPointsSystemComponent* ASkatePlayerState::GetPointsSystemComponent() const
{
	return PointsSystemComponent;
}
