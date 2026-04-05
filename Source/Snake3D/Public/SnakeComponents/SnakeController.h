// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "SnakeController.generated.h"

enum class ESnakeGameState : uint8;
/**
 * 
 */
UCLASS()
class SNAKE3D_API ASnakeController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void HandleGameStateChanged(ESnakeGameState NewState);

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* StartGameAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* ShowMainMenuAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* StartOutroAction;
	
protected:
	void virtual SetupInputComponent() override;
	void virtual BeginPlay() override;
};
