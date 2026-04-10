// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle/HazardUtilActor.h"
#include "SnakeTail.generated.h"



UCLASS()
class SNAKE3D_API ASnakeTail : public AHazardUtilActor
{
	GENERATED_BODY()

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
