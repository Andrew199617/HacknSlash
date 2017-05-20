// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "NewLevelCollider.h"
#include "HacknSlashCharacter.h"
#include "LevelGenerator.h"

ANewLevelCollider::ANewLevelCollider()
{
	levelGeneratorRef = 0;
}

void ANewLevelCollider::BeginPlay()
{
	for (TActorIterator<ALevelGenerator> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		levelGeneratorRef = *ActorItr;
		break;
	}
	characterRef = Cast<AHacknSlashCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	GetStaticMeshComponent()->SetHiddenInGame(true);
}

void ANewLevelCollider::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->GetName() == characterRef->GetName())
	{
		if (levelGeneratorRef)
		{
			levelGeneratorRef->SpawnNextTile();
		}
	}
}
