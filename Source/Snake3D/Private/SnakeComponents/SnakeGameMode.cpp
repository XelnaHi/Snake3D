// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeComponents/SnakeGameMode.h"

void ASnakeGameMode::SetGameState(ESnakeGameState NewState)
{
	CurrentState = NewState;
	UE_LOG(LogTemp, Warning, TEXT("GameState changed to %d"), (int32)NewState);
	OnGameStateChanged.Broadcast(NewState);
}

void ASnakeGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	SetGameState(ESnakeGameState::MainMenu);
}
