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
	

	// Movement
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* TurnAction;
	
	float CurrentForwardInput;
	
	void Turn(const FInputActionValue& Value);
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 650.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TurnSpeed = 120.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake Tail")
	TSubclassOf<ASnakeTail> SnakeTailClass;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> SnakeHead;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> HeadToFollow;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snake Tail")
	int32 BodyCount;
	
	UFUNCTION(BlueprintCallable, Category = "Snake Tail")
	void SpawnTail(TSubclassOf<ASnakeTail> TailClass) ;
	
private:
	FActorSpawnParameters SpawnInfo;
	TArray<ASnakeTail*> SnakeTails;
	bool bCanMove;
	
	friend class ASnakeController;
	
	void GrowTail();
	void UpdateAllBodyParts();
	
};
