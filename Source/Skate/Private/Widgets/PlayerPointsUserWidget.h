// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Widgets/Text/STextBlock.h>
#include "PlayerPointsUserWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class UPlayerPointsUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct();

private:
	void OnUpdatePoints(int Points);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PointsText;
};
