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
	
	void AddPlayerToDataMap(const int32 PlayerID);
	
	UFUNCTION(BlueprintCallable, Category="Persistent Player Data")
	FPlayerPersistentData GetSnakePlayerData(int32 PlayerID);
	
	void SetCurrentLevel(ESnakeGameLevel NewLevel);
	ESnakeGameLevel GetCurrentLevel() const {return CurrentLevel;}
	
private:
	UFUNCTION(BlueprintCallable, Category="Persistent Player Data")
	void ResetSnakeGameInstanceData();
	
	UPROPERTY(EditAnywhere, Category="Persistent Player Data")
	FPlayerPersistentData SnakePlayerData;

	TMap<int32, FPlayerPersistentData> SnakePlayerMap;
	
	ESnakeGameLevel CurrentLevel;

};
