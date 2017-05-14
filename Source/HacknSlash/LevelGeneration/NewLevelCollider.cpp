// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "NewLevelCollider.h"
#include "HacknSlashCharacter.h"
#include "LevelGenerator.h"

ANewLevelCollider::ANewLevelCollider()
{
}

void ANewLevelCollider::BeginPlay()
{
	characterRef = Cast<AHacknSlashCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	GetStaticMeshComponent()->SetHiddenInGame(true);
}

void ANewLevelCollider::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->GetName() == characterRef->GetName())
	{
		levelGeneratorRef->SpawnNextTile();
		levelGeneratorRef->UnSpawnLastTile();
	}
}
