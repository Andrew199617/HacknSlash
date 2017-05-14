// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "HacknSlash.h"
#include "HacknSlashCharacter.h"
#include "Blueprint/UserWidget.h"

AHacknSlashCharacter::AHacknSlashCharacter()
{

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

}

void AHacknSlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

}

UUserWidget* AHacknSlashCharacter::SetHud(class UUserWidget* val)
{
	hud = val;
	return hud;
}

void AHacknSlashCharacter::Tick(float DeltaTime)
{
	if (health <= 0) 
	{
		if (lives <= 0)
		{
			hud->RemoveFromViewport();

			if (gameOverClass)
			{
				gameOverWidget = CreateWidget<UUserWidget>(controller, gameOverClass);
				if (gameOverWidget)
				{
					gameOverWidget->AddToViewport();
				}
			}
		}
		else
		{
			Respawn();
		}
	}
}

void AHacknSlashCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (lives <= 0) 
	{

	}
}

void AHacknSlashCharacter::Respawn()
{
	lives--;
	health = 100;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHacknSlashCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHacknSlashCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AHacknSlashCharacter::MoveForward);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AHacknSlashCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AHacknSlashCharacter::TouchStopped);
}

void AHacknSlashCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AHacknSlashCharacter::MoveForward(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(-1.f, 0.f, 0.f), Value, true);
}

void AHacknSlashCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AHacknSlashCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

