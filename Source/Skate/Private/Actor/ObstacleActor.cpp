// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/ObstacleActor.h"
#include "Interfaces/PointsSystemInterface.h"
#include "Components/BoxComponent.h"
#include "Components/PointsSystemComponent.h"

AObstacleActor::AObstacleActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	SetRootComponent(ObstacleMesh);

	PointTriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBoxComponent"));
	PointTriggerBoxComponent->SetupAttachment(GetRootComponent());

	FailTriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("FailTriggerBoxComponent"));
	FailTriggerBoxComponent->SetupAttachment(GetRootComponent());
}

void AObstacleActor::BeginPlay()
{
	PointTriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnPointTriggerBoxOverlap);
	FailTriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnFailTriggerBeginOverlap);
	FailTriggerBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnFailTriggerEndOverlap);
}

void AObstacleActor::BeginDestroy()
{
	Super::BeginDestroy();

	if (PointTriggerBoxComponent != nullptr)
	{
		PointTriggerBoxComponent->OnComponentBeginOverlap.RemoveAll(this);
	}

	if (FailTriggerBoxComponent != nullptr)
	{
		FailTriggerBoxComponent->OnComponentBeginOverlap.RemoveAll(this);

		FailTriggerBoxComponent->OnComponentEndOverlap.RemoveAll(this);
	}

	FailedActors.Empty();
}

void AObstacleActor::OnPointTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (FailedActors.Contains(OtherActor))
	{
		return;
	}

	if (IPointsSystemInterface* PointsSystemInterface = Cast<IPointsSystemInterface>(OtherActor))
	{
		UPointsSystemComponent* PointsSystemComponent = PointsSystemInterface->GetPointsSystemComponent();

		PointsSystemComponent->AddPoints(ObstaclePoints);

#if WITH_EDITOR
		if (ObstaclePoints == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("The obstacle added 0 points as a reward, having no actual effect. %s"), *GetFName().ToString());
		}
#endif
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
