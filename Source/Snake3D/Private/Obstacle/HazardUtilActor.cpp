// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle/HazardUtilActor.h"

#include "SnakeComponents/SnakeCharacter.h"
#include "SnakeComponents/SnakeController.h"
#include "SnakeComponents/SnakeGameInstance.h"

void AHazardUtilActor::HandleSnakeOverlap(AActor* OtherActor) const
{
	const ASnakeCharacter* SnakeCharacter = Cast<ASnakeCharacter>(OtherActor);
	if (!SnakeCharacter) return;

	ASnakeController* SnakeController = Cast<ASnakeController>(SnakeCharacter->GetController());
	if (!SnakeController) return;

	USnakeGameInstance* GameInstance = GetGameInstance<USnakeGameInstance>();
	if (!GameInstance) return;

	const int32 SnakePlayerID = SnakeController->GetLocalPlayer()->GetControllerId();
	const int WinnerIndex = (SnakePlayerID == 0) ? 1 : 0;

	const FPlayerPersistentData PlayerData = GameInstance->GetSnakePlayerData(WinnerIndex);

	if (GameInstance->IsCoopMode())
	{
		SnakeController->ShowOutro(WinnerIndex + 1, PlayerData.Score);
	}
	else
	{
		SnakeController->ShowOutro(1, PlayerData.Score);
	}
}
