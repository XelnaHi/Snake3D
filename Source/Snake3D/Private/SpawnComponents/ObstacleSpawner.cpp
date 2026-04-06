// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnComponents/ObstacleSpawner.h"
#include "Components/BoxComponent.h"
#include "kismet/KismetMathLibrary.h"

AObstacleSpawner::AObstacleSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ObstacleSpawnBox"));
	SpawnBox->SetupAttachment(RootComponent);
}

void AObstacleSpawner::BeginPlay()
{
	for (int i = 0; i < SpawnAmount; ++i)
	{
		SpawnObstacle();
	}
	
	Super::BeginPlay();
}

void AObstacleSpawner::SpawnObstacle() const
{
	const FVector Center = SpawnBox->GetComponentLocation();
	const FVector Extent = SpawnBox->GetScaledBoxExtent();

	FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(Center, Extent);
	RandomPoint.Z = 0;

	if (ActorsToSpawn.Num() == 0) return;

	const int32 RandomIndex = FMath::RandRange(0, ActorsToSpawn.Num() - 1);

	if (const TSubclassOf<AActor> ChosenActor = ActorsToSpawn[RandomIndex])
	{
		GetWorld()->SpawnActor<AActor>(ChosenActor, RandomPoint, FRotator::ZeroRotator);
	}
}

void AObstacleSpawner::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

