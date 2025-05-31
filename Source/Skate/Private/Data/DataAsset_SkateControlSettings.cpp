// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataAsset_SkateControlSettings.h"

float UDataAsset_SkateControlSettings::GetPushImpulse() const
{
    return PushImpulse;
}

float UDataAsset_SkateControlSettings::GetTargetAccelerationForImpulse() const
{
    return TargetAccelerationForImpulse;
}

float UDataAsset_SkateControlSettings::GetMinAcceleration() const
{
    return MinAcceleration;
}

float UDataAsset_SkateControlSettings::GetAccelerationDuration() const
{
    return AccelerationDuration;
}

float UDataAsset_SkateControlSettings::GetTurnRate() const
{
    return TurnRate;
}
