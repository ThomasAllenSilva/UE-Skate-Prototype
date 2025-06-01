// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/PointsSystemInterface.h"
#include "SkatePlayerState.generated.h"

class UPointsSystemComponent;

/**
 *
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
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPointsSystemComponent> PointsSystemComponent;
};
