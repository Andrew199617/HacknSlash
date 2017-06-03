// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "SpawnConfiguration.h"
#include <string>
#include "Character/EnemyCharacter.h"


// Sets default values for this component's properties
USpawnConfiguration::USpawnConfiguration() : UActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bEditableWhenInherited = true;
	// ...
	numSpawns = 0;
	spawnLocation = FVector(0,0,0);
	spawnMesh = 0;
}


// Called when the game starts
void USpawnConfiguration::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters spawnParams;

		for(int i = 0; i < numSpawns; ++i)
		{
			std::string str = "Spawn" + std::to_string(i + 1);
			spawnParams.Name = str.c_str();
			int32 j = spawns.Add(world->SpawnActor<AStaticMeshActor>(spawnParams));
			if (spawnMesh)
			{
				spawns[j]->GetStaticMeshComponent()->SetStaticMesh(spawnMesh);
				spawns[j]->SetMobility(EComponentMobility::Movable);
				spawns[j]->SetActorLocation(spawnLocation);
			}
		}
	}
}


// Called every frame
void USpawnConfiguration::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	static float m_dt = 0;
	m_dt += DeltaTime;

	if (m_dt >= spawnEvery)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Name = "Spawned Enemy";
			spawnParams.Owner = GetOwner();
			
			UClass* enemyClass = spawnableEnemies.Get()->GetClass();
			UClass* enemyClass1 = spawnableEnemies->GetClass();
			UClass* enemyClass2 = spawnableEnemies.GetDefaultObject()->GetClass();
			AEnemyCharacter* spawnedEnemy = world->SpawnActor<AEnemyCharacter>(enemyClass2, spawnParams);
			spawnedEnemy->SetActorLocation(spawnLocation + FVector(0,-100, 96));
		}
		m_dt = 0;
	}
}

void USpawnConfiguration::SetLocation(FVector NewLocation)
{
	for (auto spawn : spawns)
	{
		spawn->SetActorLocation( spawn->GetActorLocation() + (NewLocation - spawn->GetActorLocation()) );
	}
}

