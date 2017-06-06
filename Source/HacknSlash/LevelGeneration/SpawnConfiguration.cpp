// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "SpawnConfiguration.h"
#include <string>
#include "Character/EnemyCharacter.h"
#include "Spawner.h"


// Sets default values for this component's properties
USpawnConfiguration::USpawnConfiguration() : UActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bEditableWhenInherited = true;
	// ...
	numSpawns = 2;
	spawnMesh = 0;
	maxEnemies = 5;
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
			int32 j = spawns.Add(world->SpawnActor<ASpawner>(spawnParams));
			if (spawnMesh)
			{
				spawns[j]->myMesh->SetStaticMesh(spawnMesh);
			}
			spawns[j]->maxEnemies = maxEnemies;
			spawns[j]->spawnEvery = spawnEvery;
			spawns[j]->myMesh->SetMobility(EComponentMobility::Movable);
			spawns[j]->SetActorLocation(spawnLocation[i]);

			spawnParams.Owner = spawns[j];
			for (int i2 = 0; i2 < maxEnemies; ++i2)
			{
				UClass* enemyClass = spawnableEnemies[i].GetDefaultObject()->GetClass();
				spawnParams.Name = ("Spawned Enemy" + std::to_string(i) + std::to_string(i2)).c_str();
				AEnemyCharacter* character = world->SpawnActor<AEnemyCharacter>(enemyClass, spawnParams);
				int32 k = spawns[j]->spawnedEnemies.Add(character);
				spawns[j]->spawnedEnemies[k]->SetActorLocation(FVector(0, 0, 100096));
			}

		}

	}
}


// Called every frame
void USpawnConfiguration::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void USpawnConfiguration::SetLocation(FVector NewLocation)
{
	for (auto spawn : spawns)
	{
		spawn->SetActorLocation( spawn->GetActorLocation() + (NewLocation - spawn->GetActorLocation()) );
	}
}

