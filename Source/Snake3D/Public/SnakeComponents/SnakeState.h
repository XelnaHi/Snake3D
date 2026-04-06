// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SnakeState.generated.h"

/**
 * 
 */


class ASnakeGameMode;
class USnakeGameInstance;

UENUM(BlueprintType)
enum class ESnakeGameLevel : uint8
{
	FirstLevel,
	SecondLevel,
	ThirdLevel
};

UCLASS()
class SNAKE3D_API ASnakeState : public APlayerState
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreUpdated, float, NewScore);

	UPROPERTY(BlueprintAssignable)
	FOnScoreUpdated OnScoreUpdated;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReachedTargetScore, ESnakeGameLevel, CurrentLevel);

	UPROPERTY(BlueprintAssignable)
	FOnReachedTargetScore OnReachedTargetScore;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
	void SetPlayerStateScore(const float NewScore) { SetScore(NewScore); }

	UFUNCTION(BlueprintCallable)
	void UpdateScore(const int32 SnakeID);

	ESnakeGameLevel CurrentLevel = ESnakeGameLevel::FirstLevel;

	TObjectPtr<USnakeGameInstance> GameInstance;
	TObjectPtr<ASnakeGameMode> SnakeGameMode;
};
