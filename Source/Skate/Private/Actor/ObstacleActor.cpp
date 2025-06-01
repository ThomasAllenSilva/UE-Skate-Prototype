// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ObstacleActor.h"
#include "Data/DataAsset_ObstacleRewardInfo.h"
#include "Interfaces/PointsSystemInterface.h"
#include "Components/BoxComponent.h"
#include "Components/PointsSystemComponent.h"

AObstacleActor::AObstacleActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	SetRootComponent(ObstacleMesh);

	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBoxComponent"));
	TriggerBoxComponent->SetupAttachment(GetRootComponent());

	FailTriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("FailTriggerBoxComponent"));
	FailTriggerBoxComponent->SetupAttachment(GetRootComponent());
}

void AObstacleActor::BeginPlay()
{
	TriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerBoxOverlap);
	FailTriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnFailTriggerBeginOverlap);
	FailTriggerBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnFailTriggerEndOverlap);
}

void AObstacleActor::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (FailedActors.Contains(OtherActor))
	{
		return;
	}

	if (IPointsSystemInterface* PointsSystemInterface = Cast<IPointsSystemInterface>(OtherActor))
	{
		UPointsSystemComponent* PointsSystemComponent = PointsSystemInterface->GetPointsSystemComponent();

		PointsSystemComponent->AddPoints(10);
	}
}

void AObstacleActor::OnFailTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IPointsSystemInterface* PointsSystemInterface = Cast<IPointsSystemInterface>(OtherActor))
	{
		FailedActors.AddUnique(OtherActor);
	}
}

void AObstacleActor::OnFailTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IPointsSystemInterface* PointsSystemInterface = Cast<IPointsSystemInterface>(OtherActor))
	{
		FailedActors.Remove(OtherActor);
	}
}
