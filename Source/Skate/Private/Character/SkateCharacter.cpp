// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SkateCharacter.h"
#include "Components/SkaterComponent.h"

ASkateCharacter::ASkateCharacter()
{
	SkaterComponent = CreateDefaultSubobject<USkaterComponent>("SkaterComponent");
}

USkaterComponent* ASkateCharacter::GetSkaterComponent()
{
	return SkaterComponent;
}
