// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeTail.generated.h"


UCLASS()
class SNAKE3D_API ASnakeTail : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

};
