// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/PointsSystemComponent.h"

UPointsSystemComponent::UPointsSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UPointsSystemComponent::AddPoints(int Points)
{
	CurrentPoints += Points;

	OnUpdatePoints.Broadcast(CurrentPoints);
}

int UPointsSystemComponent::GetCurrentPoints() const
{
	return CurrentPoints;
}
