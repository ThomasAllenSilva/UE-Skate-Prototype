// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PointsSystemComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdatePointsSignature, int);

UCLASS(ClassGroup = (PointsSystem), meta = (BlueprintSpawnableComponent))
class UPointsSystemComponent final : public UActorComponent
{
	GENERATED_BODY()

public:
	UPointsSystemComponent();

	void AddPoints(int Points);

	int GetCurrentPoints() const;

	FOnUpdatePointsSignature OnUpdatePoints;

private:
	UPROPERTY()
	int CurrentPoints;
};
