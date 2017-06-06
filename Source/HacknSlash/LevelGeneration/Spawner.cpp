// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "Spawner.h"
#include <string>
#include "Character/EnemyCharacter.h"


// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	maxEnemies = 5;
	curEnemy = 0;

	myMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	myMesh->SetupAttachment(RootComponent);
	myMesh->RegisterComponent();
}

// Called when the game starts or when spawned
void ASpawner::MyBeginPlay()
{
	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters spawnParams;

		for (int i = 0; i < maxEnemies; ++i)
		{
			spawnParams.Name = ("Spawned Enemy" + std::to_string(i)).c_str();
			int j = spawnedEnemies.Add(world->SpawnActor<AEnemyCharacter>(enemyClass, spawnParams));
			spawnedEnemies[j]->SetActorLocation(FVector(0, 0, 100096));
		}
	}
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	static float m_dt = 0;
	m_dt += DeltaTime;

	if (m_dt >= spawnEvery && curEnemy < maxEnemies)
	{
		spawnedEnemies[curEnemy]->SetActorLocation(GetActorLocation() + FVector(0, 0, 96));
		curEnemy++;
		m_dt = 0;
	}
}

