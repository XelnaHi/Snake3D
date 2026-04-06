// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeComponents/SnakeGameInstance.h"

#include "SnakeComponents/SnakeState.h"

void USnakeGameInstance::SetInstancedSnakePlayerScore(const float NewScore, const int32 PlayerID)
{
	if (SnakePlayerMap.Contains(PlayerID))
	{
		SnakePlayerMap[PlayerID].Score = NewScore;
	}
}

void USnakeGameInstance::SetInstancedSnakePlayerSpeed(const float NewSpeed, int32 PlayerID)
{
	if (SnakePlayerMap.Contains(PlayerID))
	{
		SnakePlayerMap[PlayerID].CurrentMoveSpeed = NewSpeed;
	}
}

void USnakeGameInstance::AddPlayerToDataMap(const int32 PlayerID)
{
	if (!SnakePlayerMap.Contains(PlayerID))
	{
		SnakePlayerMap.Add(PlayerID);
	}
}

FPlayerPersistentData USnakeGameInstance::GetSnakePlayerData(const int32 PlayerID)
{
	if (SnakePlayerMap.Contains(PlayerID))
	{
		return SnakePlayerMap[PlayerID];
	}
	return FPlayerPersistentData();
}

void USnakeGameInstance::SetCurrentLevel(ESnakeGameLevel NewLevel)
{
	CurrentLevel = NewLevel;
}

void USnakeGameInstance::ResetSnakeGameInstanceData()
{
	SnakePlayerMap.Empty();
	CurrentLevel = ESnakeGameLevel::FirstLevel;
}
