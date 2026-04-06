// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeComponents/SnakeGameInstance.h"

#include "SnakeComponents/SnakeState.h"

void USnakeGameInstance::SetSnakePlayerData(const float Score, const int32 PlayerID)
{
	if (SnakePlayerMap.Contains(PlayerID))
	{
		SnakePlayerMap[PlayerID] = Score;
	}
	SnakePlayerData.Score = Score;
}

void USnakeGameInstance::AddPlayerToDataMap(const int32 PlayerID)
{
	if (!SnakePlayerMap.Contains(PlayerID))
	{
		SnakePlayerMap.Add(PlayerID, 0);
	}
}

float USnakeGameInstance::GetSnakePlayerData(const int32 PlayerID)
{
	if (SnakePlayerMap.Contains(PlayerID))
	{
		return SnakePlayerMap[PlayerID];
	}
	return 0;
}

void USnakeGameInstance::SetCurrentLevel(ESnakeGameLevel NewLevel)
{
	CurrentLevel = NewLevel;
}

bool USnakeGameInstance::ResetSnakeGameInstanceData()
{
	SnakePlayerMap.Empty();
	CurrentLevel = ESnakeGameLevel::FirstLevel;
	
	return false;
}
