// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle/DangerousObstacle.h"

#include "SnakeComponents/SnakeCharacter.h"
#include "SnakeComponents/SnakeController.h"
#include "SnakeComponents/SnakeGameInstance.h"


class USnakeGameInstance;

ADangerousObstacle::ADangerousObstacle()
{
}

void ADangerousObstacle::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	HandleSnakeOverlap(OtherActor);
}
