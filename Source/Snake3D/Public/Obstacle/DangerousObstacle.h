// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeComponents/SnakeTail.h"
#include "DangerousObstacle.generated.h"


UCLASS()
class SNAKE3D_API ADangerousObstacle : public AHazardUtilActor
{
	GENERATED_BODY()

public:
	ADangerousObstacle();
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
