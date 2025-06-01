// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleActor.generated.h"

class UBoxComponent;

/*
* Used to give points to the player whenever it successfully passes through the PointTrigger
*/
UCLASS()
class AObstacleActor final : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacleActor();

protected:
	virtual void BeginPlay();
	virtual void BeginDestroy();
private:
	UFUNCTION()
	void OnPointTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnFailTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnFailTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	/* Mesh that represents the actual obstacle */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> ObstacleMesh;

	/* This trigger awards points to any actor that successfully passes through it */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> PointTriggerBoxComponent;

	/* Trigger used to identify actors that failed to pass through the PointTrigger */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> FailTriggerBoxComponent;

	/* Array of actors currently inside the Fail trigger, preventing them from receiving points */
	UPROPERTY()
	TArray<AActor*> FailedActors;

	/* The amount of points to award */
	UPROPERTY(EditDefaultsOnly)
	int ObstaclePoints;
};
