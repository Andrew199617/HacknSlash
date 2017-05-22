// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "BasePickup.h"
#include "HacknSlashCharacter.h"

AHacknSlashCharacter* ABasePickup::playerCharacter = nullptr;

// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	collider->SetSphereRadius(pickupRadius);

}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	collider->SetSphereRadius(pickupRadius);
	playerCharacter = Cast<AHacknSlashCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePickup::OnPickup()
{
	Destroy();
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (playerCharacter)
	{
		if (OtherActor->GetName() == playerCharacter->GetName())
		{
			OnPickup();
		}
	}

}

