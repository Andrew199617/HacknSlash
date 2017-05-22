// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "NewLevelCollider.h"
#include "HacknSlashCharacter.h"
#include "LevelGenerator.h"

ANewLevelCollider::ANewLevelCollider()
{
	levelGeneratorRef = 0;
}

void ANewLevelCollider::SetLevelGeneratorRef(class ALevelGenerator* val)
{
	levelGeneratorRef = val;
}

void ANewLevelCollider::BeginPlay()
{
	characterRef = Cast<AHacknSlashCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	GetStaticMeshComponent()->Mobility = EComponentMobility::Movable;
	GetStaticMeshComponent()->bGenerateOverlapEvents = true;
	GetStaticMeshComponent()->SetCollisionProfileName("OverlapAllDynamic");
	GetStaticMeshComponent()->bEditableWhenInherited = true;
	GetStaticMeshComponent()->CastShadow = false;
	GetStaticMeshComponent()->bHiddenInGame = true;
	GetStaticMeshComponent()->SetRelativeScale3D(FVector(10, 1, 10));
}

void ANewLevelCollider::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor->GetName() == characterRef->GetName() && levelGeneratorRef)
	{
		if (characterRef->GetActorLocation().Y < GetActorLocation().Y)
		{
			levelGeneratorRef->SpawnNextTile();
		}
		else {
			levelGeneratorRef->SpawnLastTile();
		}
	}
}
