// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeComponents/SnakeController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeComponents/SnakeCharacter.h"

void ASnakeController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (GetLocalPlayer()->GetControllerId() != 0) return;

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(TurnP1Action, ETriggerEvent::Triggered, this, &ASnakeController::TurnP1);
		EIC->BindAction(TurnP2Action, ETriggerEvent::Triggered, this, &ASnakeController::TurnP2);
	}
}

void ASnakeController::TurnP1(const FInputActionValue& Value) // Cant be made const. It's assigned in SetupInputComponent.
{
	if (ASnakeCharacter* Snake = Cast<ASnakeCharacter>(GetPawn()))
	{
		Snake->Turn(Value);
	}
}

void ASnakeController::TurnP2(const FInputActionValue& Value) // Cant be made const. It's assigned in SetupInputComponent.
{
	if (APlayerController* PC1 = UGameplayStatics::GetPlayerController(this, 1))
	{
		if (ASnakeCharacter* Snake = Cast<ASnakeCharacter>(PC1->GetPawn()))
		{
			Snake->Turn(Value);
		}
	}
}


void ASnakeController::BeginPlay()
{

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMapping, 0);
	}

	Super::BeginPlay();
}
