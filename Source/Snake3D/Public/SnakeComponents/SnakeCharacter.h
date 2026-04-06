// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "SnakeController.h"
#include "SnakeTail.h"
#include "GameFramework/Character.h"
#include "SnakeCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class SNAKE3D_API ASnakeCharacter : public ACharacter
{
	GENERATED_BODY()
	

public:
	ASnakeCharacter();

protected:
	
	float CurrentForwardInput;

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	bool bCanMove;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void IncreaseMoveSpeed(float Multiplier);
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 650.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnSpeed = 120.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	class UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, Category = "Snake Tail")
	TSubclassOf<ASnakeTail> SnakeTailClass;
	
	UPROPERTY(EditAnywhere, Category = "Snake Tail")
	int32 BodyCount;
	
	UPROPERTY(EditAnywhere, Category = "Snake Tail")
	int32 TailSegmentDistance;	
	
	UPROPERTY(EditAnywhere, Category = "Snake Tail")
	int32 TailLengthDistance;
	
	UPROPERTY(EditAnywhere, Category = "Snake Tail")
	float LerpTime;
	
	UPROPERTY(EditAnywhere, Category= "Snake Head")
	TObjectPtr<UStaticMeshComponent> SnakeHead;
	
	UPROPERTY(EditAnywhere, Category= "Snake Head")
	TObjectPtr<UStaticMeshComponent> HeadToFollow;
	
	FActorSpawnParameters SpawnInfo;
	TArray<ASnakeTail*> SnakeTails;
	

	UFUNCTION(BlueprintCallable, Category = "Snake Tail")
	void GrowTail();
	
	UFUNCTION(BlueprintCallable, Category = "Snake Tail")
	void SpawnTail(TSubclassOf<ASnakeTail> TailClass) ;
	
	void UpdateAllBodyParts();
	void Turn(const FInputActionValue& Value);
	
	friend class ASnakeController;
	
};
