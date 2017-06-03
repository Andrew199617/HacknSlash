// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "EnemyCharacter.h"
#include "HacknSlashCharacter.h"

AEnemyCharacter::AEnemyCharacter() : ABaseCharacter()
{

	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f, false);
	GetCapsuleComponent()->SetCapsuleRadius(42.0f);

	GetMovementComponent()->NavAgentProps.AgentRadius = 42;
	GetMovementComponent()->NavAgentProps.AgentHeight = 192;

	characterRef = 0;
}

void AEnemyCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && (OtherActor != this))
	{
		if (characterRef && OtherActor->GetName() == characterRef->GetName())
		{
			characterRef->RecieveDamage(15);
		}
	}
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	characterRef = Cast<AHacknSlashCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (health <= 0)
	{
		Destroy();
	}
}
