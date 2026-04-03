// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SnakeState.generated.h"

/**
 * 
 */
UCLASS()
class SNAKE3D_API ASnakeState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetSnakeScore(float NewScore);
	
};
