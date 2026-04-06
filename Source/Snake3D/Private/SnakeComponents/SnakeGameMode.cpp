// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeComponents/SnakeGameMode.h"
#include "SnakeComponents/SnakeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeComponents/SnakeState.h"

void ASnakeGameMode::SetGameState(ESnakeGameState NewState)
{
	CurrentState = NewState;
	OnGameStateChanged.Broadcast(NewState);
}

void ASnakeGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (!NewPlayer) return;

	const ULocalPlayer* LocalPlayer = NewPlayer->GetLocalPlayer();
	if (!LocalPlayer) return;

	const int32 PlayerIndex = LocalPlayer->GetControllerId();

	if (USnakeGameInstance* SnakeGameInstance = GetGameInstance<USnakeGameInstance>())
	{
		SnakeGameInstance->AddPlayerToDataMap(PlayerIndex);
	}
	
	if (ASnakeState* SnakeState = NewPlayer->GetPlayerState<ASnakeState>())
	{
		SnakeState->OnReachedTargetScore.AddDynamic(this, &ASnakeGameMode::HandleReachedTargetScore);
	}
}

void ASnakeGameMode::BeginPlay()
{
	SetGameState(ESnakeGameState::MainMenu);
	UGameplayStatics::CreatePlayer(GetWorld(), 1, true);

	
	Super::BeginPlay();
	
}

void ASnakeGameMode::HandleReachedTargetScore(const ESnakeGameLevel Level) // Cant be made const. Is dynamically assigned in PostLogin.
{
	switch (Level)
	{
	case ESnakeGameLevel::SecondLevel:
			UGameplayStatics::OpenLevel(GetWorld(),"Lvl_ThirdPerson");
		break;
		case ESnakeGameLevel::ThirdLevel:
			UGameplayStatics::OpenLevel(GetWorld(),"Lvl_SnakeLevel_01");
		break;
	}
}
