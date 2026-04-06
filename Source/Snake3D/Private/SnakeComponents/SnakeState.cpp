// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeComponents/SnakeState.h"
#include "SnakeComponents/SnakeGameInstance.h"
#include "SnakeComponents/SnakeGameMode.h"

void ASnakeState::BeginPlay()
{
	GameInstance = Cast<USnakeGameInstance>(GetGameInstance());
	SnakeGameMode = Cast<ASnakeGameMode>(GetWorld()->GetAuthGameMode());
	CurrentLevel = GameInstance->GetCurrentLevel();
	Super::BeginPlay();
}




void ASnakeState::UpdateScore(const int32 SnakeID)
{
	const float InstancedScore = GameInstance->GetSnakePlayerData(SnakeID).Score + 1;
	SetScore(InstancedScore);

	GameInstance->SetInstancedSnakePlayerScore(InstancedScore, SnakeID);
	OnScoreUpdated.Broadcast(InstancedScore);

	if (InstancedScore == SnakeGameMode->GetLevelOneScoreThreshold() && CurrentLevel == ESnakeGameLevel::FirstLevel)
	{
		CurrentLevel = ESnakeGameLevel::SecondLevel;
		GameInstance->SetCurrentLevel(ESnakeGameLevel::SecondLevel);
		GameInstance->SetInstancedSnakePlayerScore(InstancedScore, SnakeID);
		OnReachedTargetScore.Broadcast(CurrentLevel);
	}
	else if (InstancedScore == SnakeGameMode->GetLevelTwoScoreThreshold() && CurrentLevel == ESnakeGameLevel::SecondLevel)
	{
		CurrentLevel = ESnakeGameLevel::ThirdLevel;
		GameInstance->SetCurrentLevel(ESnakeGameLevel::ThirdLevel);
		OnReachedTargetScore.Broadcast(CurrentLevel);
	}
	else if (InstancedScore == SnakeGameMode->GetLevelThreeScoreThreshold() && CurrentLevel == ESnakeGameLevel::ThirdLevel)
	{
		OnReachedTargetScore.Broadcast(CurrentLevel);
	}
}
