// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "BasePickup.h"
#include "HacknSlashCharacter.h"

// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pickupRadius = 5;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	collider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	collider->SetSphereRadius(pickupRadius);
	collider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();

	collider->SetSphereRadius(pickupRadius);
	playerCharacter = Cast<AHacknSlashCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	bShouldDestroy = true;
}

void ABasePickup::OnPickup(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Implement On Pickup"));
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePickup::DestroySafe()
{
	if (bShouldDestroy)
	{
		Destroy();
	}
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (playerCharacter)
	{
		if (OtherActor->GetName() == playerCharacter->GetName())
		{
			OnPickup(OtherActor);
			DestroySafe();
		}
	}

}

