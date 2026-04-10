// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeComponents/SnakeTail.h"

#include "GameFramework/PlayerState.h"
#include "SnakeComponents/SnakeCharacter.h"
#include "SnakeComponents/SnakeController.h"
#include "SnakeComponents/SnakeGameInstance.h"


void ASnakeTail::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	HandleSnakeOverlap(OtherActor);
}
