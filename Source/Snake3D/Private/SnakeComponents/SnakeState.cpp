// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeComponents/SnakeState.h"
#include "SnakeComponents/SnakeGameInstance.h"
#include "SnakeComponents/SnakeGameMode.h"

void ASnakeState::BeginPlay()
{
	GameInstance = Cast<USnakeGameInstance>(GetGameInstance());
	SnakeGameMode = Cast<ASnakeGameMode>(GetWorld()->GetAuthGameMode());
	Super::BeginPlay();
}

void ASnakeState::UpdateScore(const int32 SnakeID)
{
	const float InstancedScore = GameInstance->GetSnakePlayerData(SnakeID).Score + 1;
	SetScore(InstancedScore);

	GameInstance->SetInstancedSnakePlayerScore(InstancedScore, SnakeID);
	OnScoreUpdated.Broadcast(InstancedScore); // Subscribed to by WBP_ScoreLabel

	if (InstancedScore == GameInstance->GetLevelScoreThreshold())
	{
		GameInstance->SetInstancedSnakePlayerScore(InstancedScore, SnakeID);
		GameInstance->IncreaseLevelScoreThreshold();
		OnReachedTargetScore.Broadcast();
	}

}
