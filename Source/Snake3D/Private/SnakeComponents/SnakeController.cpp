// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeComponents/SnakeController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SnakeComponents/SnakeCharacter.h"
#include "SnakeComponents/SnakeGameInstance.h"
#include "SnakeComponents/SnakeGameMode.h"

void ASnakeController::HandleGameStateChanged(ESnakeGameState NewState)
{
		// switch (NewState)
		// {
		// case ESnakeGameState::MainMenu:
		// 	{
		// 		UE_LOG(LogTemp, Warning, TEXT("Entered MainMenu"));
		//
		// 		SetShowMouseCursor(true);
		// 		if (ASnakeCharacter* SnakeChar = Cast<ASnakeCharacter>(GetPawn()))
		// 		{
		// 			SnakeChar->bCanMove = false;
		// 		}
		// 		break;
		// 	}
		// case ESnakeGameState::Game:
		// 	{
		// 		UE_LOG(LogTemp, Warning, TEXT("Entered Game"));
		//
		// 		SetShowMouseCursor(false);
		// 		if (ASnakeCharacter* SnakeChar = Cast<ASnakeCharacter>(GetPawn()))
		// 		{
		// 			SnakeChar->bCanMove = true;
		// 		}
		// 		break;
		// 	}
		// case ESnakeGameState::Outro:
		// 	{
		// 		UE_LOG(LogTemp, Warning, TEXT("Entered Outro"));
		//
		// 		if (ASnakeCharacter* SnakeChar = Cast<ASnakeCharacter>(GetPawn()))
		// 		{
		// 			SnakeChar->bCanMove = false;
		// 		}
		// 		break;
		// 	}
		// }
}

void ASnakeController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// TODO: Add pause menu handling here
	}
}


void ASnakeController::BeginPlay()
{

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMapping, 0);
	}

	ASnakeGameMode* GameMode = GetWorld()->GetAuthGameMode<ASnakeGameMode>();
	if (GameMode)
	{
		// GameMode->OnGameStateChanged.AddDynamic(this, &ASnakeController::HandleGameStateChanged);
	}
	
	Super::BeginPlay();
	
}
