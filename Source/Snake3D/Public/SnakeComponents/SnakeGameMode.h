// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameMode.generated.h"

enum class ESnakeGameLevel: uint8;
/**
 * 
 */
	UENUM(BlueprintType)
	enum class ESnakeGameState : uint8
	{
		MainMenu,
		Game,
		Outro
	};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, ESnakeGameState, NewState);


UCLASS()
class SNAKE3D_API ASnakeGameMode : public AGameModeBase
{
	GENERATED_BODY()

	public:
	
	float GetLevelOneScoreThreshold() const { return LevelOneScoreThreshold; };
	float GetLevelTwoScoreThreshold() const { return LevelTwoScoreThreshold; };
	float GetLevelThreeScoreThreshold() const { return LevelThreeScoreThreshold; };
	
	UPROPERTY(BlueprintReadOnly)
	ESnakeGameState CurrentState;
	
	UPROPERTY(BlueprintAssignable)
	FOnGameStateChanged OnGameStateChanged; 

	UFUNCTION(BlueprintCallable)
	void SetGameState(ESnakeGameState NewState);
	
	void virtual PostLogin(APlayerController* NewPlayer) override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Level Score Threshold")
	float LevelOneScoreThreshold = 10;
	
	UPROPERTY(EditAnywhere, Category = "Level Score Threshold")
	float LevelTwoScoreThreshold = 15;
	
	UPROPERTY(EditAnywhere, Category = "Level Score Threshold")
	float LevelThreeScoreThreshold = 20;
	
	UFUNCTION()
	void HandleReachedTargetScore(ESnakeGameLevel Level);
	
};
	