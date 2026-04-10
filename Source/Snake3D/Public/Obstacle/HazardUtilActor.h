// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HazardUtilActor.generated.h"

UCLASS()
class SNAKE3D_API AHazardUtilActor : public AActor
{
	GENERATED_BODY()

protected:
	void HandleSnakeOverlap(AActor* OtherActor) const;
};
