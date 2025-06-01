// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PointsSystemInterface.generated.h"

class UPointsSystemComponent;

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UPointsSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for actors that expose access to the points system component
 */
class IPointsSystemInterface
{
	GENERATED_BODY()

public:
	/** Returns the points system component to use for this actor */
	virtual UPointsSystemComponent* GetPointsSystemComponent() const = 0;
};
