// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

UCLASS()
class SNAKE3D_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()

public:
	AObstacleSpawner();
	void virtual Tick(float DeltaTime) override;	

	
protected:
	virtual void BeginPlay() override;

private:
		
	UPROPERTY(EditAnywhere, Category="Spawning")
	TObjectPtr<UBoxComponent> SpawnBox;

	UPROPERTY(EditAnywhere, Category="Spawning")
	TArray<TSubclassOf<AActor>> ActorsToSpawn;

	UPROPERTY(EditAnywhere, Category="Spawning")
	int32 SpawnAmount = 15;
	
	UPROPERTY(EditAnywhere, Category="Spawning")
	float SpawnsMultiplier = 1;

	
	void SpawnObstacle() const;
};
