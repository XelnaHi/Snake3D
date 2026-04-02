// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
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
	virtual void BeginPlay() override;
	

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
	
	
};
