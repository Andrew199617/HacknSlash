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
	enemyToSpawn = 0;
	spawnRadius = false;

	myMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	myMesh->SetupAttachment(RootComponent);
	myMesh->RegisterComponent();
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (world && enemyToSpawn)
	{
		for (int i2 = 0; i2 < maxEnemies; ++i2)
		{
			AEnemyCharacter* character = world->SpawnActor<AEnemyCharacter>(enemyToSpawn, FVector(0, 0, 100096), GetActorRotation());
			spawnedEnemies.Add(character);
		}
	}
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	static float m_dt = 0;
	if (spawnRadius || !enemyToSpawn) {
		m_dt += DeltaTime;
		if (m_dt >= spawnEvery && curEnemy < maxEnemies)
		{
			spawnedEnemies[curEnemy]->SetActorLocation(GetActorLocation() + FVector(0, 0, 96));
			curEnemy++;
			m_dt = 0;
		}
	}

}

void ASpawner::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	spawnRadius = true;
}

void ASpawner::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	spawnRadius = false;
}

