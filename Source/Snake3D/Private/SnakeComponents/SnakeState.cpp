// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeComponents/SnakeState.h"

#include "SnakeComponents/SnakeGameInstance.h"


void ASnakeState::SetSnakeScore(const int32 SnakeID, const float NewScore)
{
	SetScore(NewScore);
	
	if (GetScore() == 5 && CurrentLevel == ESnakeGameLevel::FirstLevel)
	{
		CurrentLevel = ESnakeGameLevel::SecondLevel;
		GameInstance->SetInstancedSnakePlayerScore(NewScore, SnakeID);
		OnReachedTargetScore.Broadcast(CurrentLevel);
	}
	else if (GetScore() == 10 && CurrentLevel == ESnakeGameLevel::SecondLevel)
	{
		CurrentLevel = ESnakeGameLevel::ThirdLevel;
		OnReachedTargetScore.Broadcast(CurrentLevel);
	}
	else if (GetScore() == 15 && CurrentLevel == ESnakeGameLevel::ThirdLevel)
	{
		OnReachedTargetScore.Broadcast(CurrentLevel);
	}
	
}

void ASnakeState::BeginPlay()
{
	GameInstance = Cast<USnakeGameInstance>(GetGameInstance());
	CurrentLevel = GameInstance->GetCurrentLevel();
	Super::BeginPlay();
}

void ASnakeState::UpdateScore(const int32 SnakeID){
	const float OldScore = GetScore();
	const float NewScore = OldScore + 1;
	
	const float InstancedScore = GameInstance->GetSnakePlayerData(SnakeID).Score + 1;
	SetScore(InstancedScore);
	
	GameInstance->SetInstancedSnakePlayerScore(InstancedScore, SnakeID);
	OnScoreUpdated.Broadcast(InstancedScore);
	
	if (NewScore == 5 && CurrentLevel == ESnakeGameLevel::FirstLevel)
	{
		CurrentLevel = ESnakeGameLevel::SecondLevel;
		GameInstance->SetCurrentLevel(ESnakeGameLevel::SecondLevel);
		GameInstance->SetInstancedSnakePlayerScore(InstancedScore, SnakeID);
		OnReachedTargetScore.Broadcast(CurrentLevel);
	}
	else if (InstancedScore == 10 && CurrentLevel == ESnakeGameLevel::SecondLevel)
	{
		CurrentLevel = ESnakeGameLevel::ThirdLevel;
		GameInstance->SetCurrentLevel(ESnakeGameLevel::ThirdLevel);
		OnReachedTargetScore.Broadcast(CurrentLevel);
	}
	else if (InstancedScore == 15 && CurrentLevel == ESnakeGameLevel::ThirdLevel)
	{
		OnReachedTargetScore.Broadcast(CurrentLevel);
	}
}
