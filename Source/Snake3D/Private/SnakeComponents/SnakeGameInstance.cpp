// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeComponents/SnakeGameInstance.h"

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

void USnakeGameInstance::SetInstancedSnakePlayerLerp(const float NewLerpTime, int32 PlayerID)
{
	if (SnakePlayerMap.Contains(PlayerID))
	{
		SnakePlayerMap[PlayerID].LerpTime = NewLerpTime;
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


void USnakeGameInstance::IncreaseLevelScoreThreshold()
{
	LevelScoreThreshold *= LevelScoreThresholdMultiplier;
}

void USnakeGameInstance::ResetSnakeGameInstanceData(const bool bShouldResetPlayers)
{
	SnakePlayerMap.Empty();
	LevelScoreThreshold = 10;
	bIsCoopMode = false;

	if (bShouldResetPlayers)
	{
		TArray<ULocalPlayer*> LocalSnakePlayers = GetLocalPlayers();
		for (int32 i = LocalSnakePlayers.Num() - 1; i >= 1; --i)
		{
			ULocalPlayer* ExtraPlayer = LocalSnakePlayers[i];
			if (!ExtraPlayer) continue;

			RemoveLocalPlayer(ExtraPlayer);
		}
	}
}
