// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameMode.generated.h"

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
	UPROPERTY(BlueprintReadOnly)
	ESnakeGameState CurrentState;
	
	UPROPERTY(BlueprintAssignable)
	FOnGameStateChanged OnGameStateChanged; 

	UFUNCTION(BlueprintCallable)
	void SetGameState(ESnakeGameState NewState);
	
protected:
	virtual void BeginPlay() override;
};
	