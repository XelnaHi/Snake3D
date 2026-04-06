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
	
	// Movement
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* TurnP1Action;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* TurnP2Action;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;
	
protected:
	void virtual SetupInputComponent() override;
	void virtual BeginPlay() override;
	
	void TurnP1(const FInputActionValue& Value);
	void TurnP2(const FInputActionValue& Value);
};
