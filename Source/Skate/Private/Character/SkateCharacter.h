// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "SkateCharacter.generated.h"

class USkaterComponent;

UCLASS()
class ASkateCharacter final : public ACharacter
{
	GENERATED_BODY()

public:
	ASkateCharacter();

	USkaterComponent* GetSkaterComponent();

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkaterComponent> SkaterComponent;
};
