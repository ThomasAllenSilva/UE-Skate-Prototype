// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleActor.generated.h"

class UDataAsset_ObstacleRewardInfo;
class UBoxComponent;

UCLASS()
class AObstacleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacleActor();

protected:
	virtual void BeginPlay();

private:
	UFUNCTION()
	void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnFailTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnFailTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataAsset_ObstacleRewardInfo> ObstacleRewardInfo;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> ObstacleMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> TriggerBoxComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> FailTriggerBoxComponent;

	UPROPERTY()
	TArray<AActor*> FailedActors;
};
