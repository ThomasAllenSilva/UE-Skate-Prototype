// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/PointsSystemInterface.h"
#include "SkatePlayerState.generated.h"

class UPointsSystemComponent;

/**
 * Default PlayerState class used for this project. It contains information about the PointsSystem
 */
UCLASS()
class ASkatePlayerState final : public APlayerState, public IPointsSystemInterface
{
	GENERATED_BODY()

public:
	ASkatePlayerState();

	//~PointsSystem Interface
	virtual UPointsSystemComponent* GetPointsSystemComponent() const;
	//~ End of PointsSystem Interface

private:
	/* The component that holds the points informations */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPointsSystemComponent> PointsSystemComponent;
};
