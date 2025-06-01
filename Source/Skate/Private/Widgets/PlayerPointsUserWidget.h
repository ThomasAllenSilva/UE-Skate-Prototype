// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerPointsUserWidget.generated.h"

class UTextBlock;
class UPointsSystemComponent;

/**
 * 
 */
UCLASS()
class UPlayerPointsUserWidget final : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct();
	virtual void NativeDestruct();

private:
	/* Callback for when the player points is updated*/
	void OnUpdatePoints(int Points);

private:
	/* The text used for displaying the current points */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PointsText;

	/* The points system component that this widget is listening to */
	UPROPERTY()
	TObjectPtr<UPointsSystemComponent> PointsSystemComponent;
};
