// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "EnemyCharacter.h"
#include "HacknSlashCharacter.h"

void AEnemyCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && (OtherActor != this))
	{
		if (OtherActor->GetName() == characterRef->GetName())
		{
			characterRef->TakeDamage(25);
		}
	}
}

void AEnemyCharacter::BeginPlay()
{
	characterRef = Cast<AHacknSlashCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	FVector myLocation = GetActorLocation();
	FVector direction = characterRef->GetActorLocation() - myLocation;
	direction.Normalize(); 
	FVector Vel = (direction * 10 * DeltaTime);
	SetActorLocation(myLocation + Vel);
}
