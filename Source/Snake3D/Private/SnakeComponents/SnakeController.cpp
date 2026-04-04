// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeComponents/SnakeController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SnakeComponents/SnakeCharacter.h"
#include "SnakeComponents/SnakeGameMode.h"

void ASnakeController::HandleGameStateChanged(ESnakeGameState NewState)
{
	switch (NewState)
	{
	case ESnakeGameState::MainMenu:
		{
			UE_LOG(LogTemp, Warning, TEXT("Entered MainMenu"));

			SetShowMouseCursor(true);
			if (ASnakeCharacter* SnakeChar = Cast<ASnakeCharacter>(GetPawn()))
			{
				SnakeChar->bCanMove = false;
			}
			break;
		}
	case ESnakeGameState::Game:
		{
			UE_LOG(LogTemp, Warning, TEXT("Entered Game"));

			SetShowMouseCursor(false);
			if (ASnakeCharacter* SnakeChar = Cast<ASnakeCharacter>(GetPawn()))
			{
				SnakeChar->bCanMove = true;
			}
			break;
		}
	case ESnakeGameState::Outro:
		{
			UE_LOG(LogTemp, Warning, TEXT("Entered Outro"));

			if (ASnakeCharacter* SnakeChar = Cast<ASnakeCharacter>(GetPawn()))
			{
				SnakeChar->bCanMove = false;
			}
			break;
		}
	}
}

void ASnakeController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(StartGameAction, ETriggerEvent::Completed, this, &ASnakeController::StartGame);
		EIC->BindAction(ShowMainMenuAction, ETriggerEvent::Completed, this, &ASnakeController::ShowMainMenu);
		EIC->BindAction(StartOutroAction, ETriggerEvent::Completed, this, &ASnakeController::StartOutro);
	}
}

void ASnakeController::StartGame()
{
	ASnakeGameMode* GameMode = GetWorld()->GetAuthGameMode<ASnakeGameMode>();
	if (GameMode)
	{
		GameMode->SetGameState(ESnakeGameState::Game);
	}
}

void ASnakeController::ShowMainMenu()
{
	ASnakeGameMode* GameMode = GetWorld()->GetAuthGameMode<ASnakeGameMode>();
	if (GameMode)
	{
		GameMode->SetGameState(ESnakeGameState::MainMenu);
	}
}

void ASnakeController::StartOutro()
{
	ASnakeGameMode* GameMode = GetWorld()->GetAuthGameMode<ASnakeGameMode>();
	if (GameMode)
	{
		GameMode->SetGameState(ESnakeGameState::Outro);
	}
}

void ASnakeController::BeginPlay()
{
	Super::BeginPlay();


	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMapping, 0);
	}

	ASnakeGameMode* GameMode = GetWorld()->GetAuthGameMode<ASnakeGameMode>();
	if (GameMode)
	{
		GameMode->OnGameStateChanged.AddDynamic(this, &ASnakeController::HandleGameStateChanged);
	}
}
