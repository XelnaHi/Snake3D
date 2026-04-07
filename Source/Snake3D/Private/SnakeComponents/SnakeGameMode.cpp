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
	const USnakeGameInstance* GameInstance = Cast<USnakeGameInstance>(GetGameInstance());
	SetGameState(ESnakeGameState::MainMenu);

	if (GameInstance->IsCoopMode())
	{
		UGameplayStatics::CreatePlayer(GetWorld(), 1, true);
	}

	Super::BeginPlay();
}

void ASnakeGameMode::HandleReachedTargetScore() // Cant be made const. Is dynamically assigned in PostLogin.
{
	if (LevelNames.Num() == 0) return;

	const FName CurrentLevel = FName(*UGameplayStatics::GetCurrentLevelName(GetWorld(), true));

	TArray<FName> ValidLevels;

	for (const FName& Level : LevelNames)
	{
		if (Level != CurrentLevel)
		{
			ValidLevels.Add(Level);
		}
	}

	if (ValidLevels.Num() == 0) return;

	const int32 RandomIndex = FMath::RandRange(0, ValidLevels.Num() - 1);
	const FName RandomLevel = ValidLevels[RandomIndex];

	UGameplayStatics::OpenLevel(GetWorld(), RandomLevel);
}
