// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SnakeGameInstance.generated.h"

enum class ESnakeGameLevel : uint8;
enum class ESnakeGameState : uint8;

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerPersistentData
{
	UPROPERTY(BlueprintReadWrite, Category="Persistent Player Data")
	int32 Score;

	UPROPERTY(BlueprintReadWrite, Category="Persistent Player Data")
	float CurrentMoveSpeed = 650.0f;

	float LerpTime;
	
	GENERATED_BODY()
};

UCLASS()
class SNAKE3D_API USnakeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Persistent Player Data")
	void SetInstancedSnakePlayerScore(const float NewScore, int32 PlayerID);

	UFUNCTION(BlueprintCallable, Category="Persistent Player Data")
	void SetInstancedSnakePlayerSpeed(const float NewSpeed, int32 PlayerID);
	
	UFUNCTION(BlueprintCallable, Category="Persistent Player Data")
	void SetInstancedSnakePlayerLerp(const float NewLerpTime, int32 PlayerID);

	void AddPlayerToDataMap(const int32 PlayerID);

	UFUNCTION(BlueprintCallable, Category="Persistent Player Data")
	FPlayerPersistentData GetSnakePlayerData(int32 PlayerID);

	int32 GetLevelScoreThreshold() const { return LevelScoreThreshold; }
	void IncreaseLevelScoreThreshold();

	UPROPERTY(EditAnywhere, Category="Level Score Threshold")
	int32 LevelScoreThreshold;
	
	UPROPERTY(EditAnywhere, Category="Level Score Threshold")
	float LevelScoreThresholdMultiplier;
		
	UFUNCTION(BlueprintCallable)
	void SetCoopMode(const bool NewCoopMode) { bIsCoopMode = NewCoopMode; };
	
	UFUNCTION(BlueprintCallable)
	bool IsCoopMode() const { return bIsCoopMode; };

private:
	UFUNCTION(BlueprintCallable, Category="Persistent Player Data")
	void ResetSnakeGameInstanceData(bool bShouldResetPlayers);

	UPROPERTY(EditAnywhere, Category="Persistent Player Data")
	FPlayerPersistentData SnakePlayerData;

	TMap<int32, FPlayerPersistentData> SnakePlayerMap;
	
	bool bIsCoopMode;
	
};
