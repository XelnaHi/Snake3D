// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnComponents/FoodSpawner.h"
#include "Components/BoxComponent.h"
#include "kismet/KismetMathLibrary.h"

AFoodSpawner::AFoodSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FoodSpawnBox"));
	SpawnBox->SetupAttachment(RootComponent);
}

void AFoodSpawner::BeginPlay()
{
	for (int i = 0; i < InitialSpawnAmount; ++i)
	{
		SpawnFood();
	}
	
	Super::BeginPlay();
}

void AFoodSpawner::SpawnFood() const
{
	const FVector Center = SpawnBox->GetComponentLocation();
	const FVector Extent = SpawnBox->GetScaledBoxExtent();

	FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(Center, Extent);
	RandomPoint.Z = 0;
	GetWorld()->SpawnActor<AActor>(ActorToSpawn, RandomPoint, FRotator::ZeroRotator);
}

void AFoodSpawner::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SpawnCooldownCounter += DeltaSeconds;
	if (SpawnCooldownCounter >= SpawnCooldown)
	{
		SpawnFood();
		SpawnCooldownCounter = 0;
	}
}
