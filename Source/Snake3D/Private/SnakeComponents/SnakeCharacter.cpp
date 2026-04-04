// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake3D/Public/SnakeComponents/SnakeCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SnakeComponents/SnakeTail.h"
#include "kismet/KismetMathLibrary.h"


// Sets default values
ASnakeCharacter::ASnakeCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->TargetOffset = FVector(0.0f, 0.0f, 500.0f);
	CameraBoom->bDoCollisionTest = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	Camera->bUsePawnControlRotation = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	SnakeHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SnakeHead"));
	SnakeHead->SetupAttachment(RootComponent);

	HeadToFollow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadToFollow"));
	HeadToFollow->SetupAttachment(SnakeHead);
	HeadToFollow->SetRelativeLocation(FVector(-160.0f, 0.0f, 40.0f));

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

void ASnakeCharacter::BeginPlay()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
	SpawnTail(SnakeTailClass);

	for (int i = 0; i < 3; ++i)
	{
		GrowTail();
	}

	Super::BeginPlay();
}

void ASnakeCharacter::SpawnTail(const TSubclassOf<ASnakeTail> TailClass)
{
	const FVector Location = HeadToFollow->GetComponentLocation();
	FVector TempLocation = Location;

	for (int i = 0; i < BodyCount; ++i)
	{
		const int32 BodySegmentSeparationDistance = i * 50;
		const FVector SegmentLocation = FVector(BodySegmentSeparationDistance, 0.0f, 0.0f);
		TempLocation -= SegmentLocation;
		FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);

		ASnakeTail* TailPart = GetWorld()->SpawnActor<ASnakeTail>(TailClass, TempLocation, Rotation, SpawnInfo);
		// Scale of actor has been set in SnakeTailActor BP.
		TempLocation = Location;

		SnakeTails.Add(TailPart);
	}
}

void ASnakeCharacter::GrowTail()
{
	if (SnakeTails.Num() == 0) return;
	const ASnakeTail* LastBodyPart = SnakeTails.Last();
	if (!LastBodyPart) return;

	const FVector PreviousLocation = LastBodyPart->GetActorLocation();
	const FVector NewLocation = FVector(PreviousLocation.X - 50, PreviousLocation.Y, PreviousLocation.Z);
	const FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
	const FTransform NewTransform = LastBodyPart->GetTransform();

	ASnakeTail* NewLastBodyPart = GetWorld()->SpawnActor<ASnakeTail>(SnakeTailClass, NewLocation, Rotation, SpawnInfo);

	if (!NewLastBodyPart) return;

	SnakeTails.Add(NewLastBodyPart);
}

void ASnakeCharacter::UpdateAllBodyParts()
{
	if (SnakeTails.Num() == 0) return;

	ASnakeTail* FirstBodyPart = SnakeTails[0];
	if (!FirstBodyPart) return;

	FVector FirstAfterHeadLocation = FirstBodyPart->GetActorLocation();
	FVector HeadLocation = HeadToFollow->GetComponentLocation();

	FTransform FirstAfterHeadTransform = FirstBodyPart->GetTransform();
	FTransform HeadTransform = HeadToFollow->GetComponentTransform();


	float Length = UKismetMathLibrary::VSize(FirstAfterHeadLocation - HeadLocation);
	if (Length >= 100)
	{
		FTransform NewTransform = UKismetMathLibrary::TLerp(FirstAfterHeadTransform, HeadTransform, 0.05f);
		FirstBodyPart->SetActorTransform(NewTransform);
	}

	for (int i = SnakeTails.Num() - 1; i > 0; --i)
	{
		ASnakeTail* PartToMove = SnakeTails[i];
		ASnakeTail* PartToMoveTo = SnakeTails[i - 1];

		FirstAfterHeadLocation = PartToMove->GetActorLocation();
		HeadLocation = PartToMoveTo->GetActorLocation();

		FTransform FirstTransform = PartToMove->GetTransform();
		FTransform NextTransform = PartToMoveTo->GetTransform();

		Length = UKismetMathLibrary::VSize(FirstAfterHeadLocation - HeadLocation);
		if (Length >= 100)
		{
			FTransform NewTransform = UKismetMathLibrary::TLerp(FirstTransform, NextTransform, 0.05f);
			PartToMove->SetActorTransform(NewTransform);
		}
	}
}


void ASnakeCharacter::Turn(const FInputActionValue& Value)
{
	const float TurnInput = Value.Get<float>();

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += TurnInput * TurnSpeed * GetWorld()->GetDeltaSeconds();
	SetActorRotation(NewRotation);
}


void ASnakeCharacter::Tick(float DeltaTime)
{
	if (!bCanMove) return;
	Super::Tick(DeltaTime);
	AddMovementInput(GetActorForwardVector(), MoveSpeed * DeltaTime);
	UpdateAllBodyParts();
}

void ASnakeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ASnakeCharacter::Turn);
	}
}
