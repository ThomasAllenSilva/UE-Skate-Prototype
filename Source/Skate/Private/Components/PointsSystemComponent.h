// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PointsSystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdatePointsSignature, int);

/*
* Manages a point system for the owning actor
*/
UCLASS(ClassGroup = (PointsSystem), meta = (BlueprintSpawnableComponent))
class UPointsSystemComponent final : public UActorComponent
{
	GENERATED_BODY()

public:
	UPointsSystemComponent();

	/* Adds to the current points and notifies listeners about the change */
	void AddPoints(int Points);

	/* Delegate broadcasted whenever this component points changes */
	FOnUpdatePointsSignature OnUpdatePoints;

	int GetCurrentPoints() const;

private:
	/* The current points that the owner of this component has */
	UPROPERTY()
	int CurrentPoints;
};
