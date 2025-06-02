// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/PlayerPointsUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/PointsSystemInterface.h"
#include "Components/PointsSystemComponent.h"
#include "GameFramework/PlayerState.h"
#include "Components/TextBlock.h"

void UPlayerPointsUserWidget::NativeConstruct()
{
	APlayerState* PlayerState = UGameplayStatics::GetPlayerState(this, 0);

	check(PlayerState);

	IPointsSystemInterface* PointsSystemInterface = CastChecked<IPointsSystemInterface>(PlayerState);

	PointsSystemComponent = PointsSystemInterface->GetPointsSystemComponent();

	PointsSystemComponent->OnUpdatePoints.AddUObject(this, &ThisClass::OnUpdatePoints);

	UpdatePointsText(PointsSystemComponent->GetCurrentPoints());
}

void UPlayerPointsUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (PointsSystemComponent)
	{
		PointsSystemComponent->OnUpdatePoints.RemoveAll(this);
	}
}

void UPlayerPointsUserWidget::OnUpdatePoints(int Points)
{
	UpdatePointsText(Points);
}

void UPlayerPointsUserWidget::UpdatePointsText(int Points)
{
	FText PointsValueText = FText::AsNumber(Points);

	FText FinalText = FText::Format(FText::FromString("Points: {0}"), PointsValueText);

	PointsText->SetText(FinalText);
}
