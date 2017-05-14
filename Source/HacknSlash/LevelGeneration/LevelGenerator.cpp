// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "LevelGenerator.h"


// Sets default values
ALevelGenerator::ALevelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();
	/*if (curTile == 0)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			const FVector& Location = FVector(0.0f, 0.0f, 0.0f);
			const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters();
			const FRotator& Rotation = FRotator();
			UStaticMesh* mesh = CreateDefaultSubobject<UStaticMesh>(TEXT("Module"));
		}
	}*/
}

// Called every frame
void ALevelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelGenerator::SpawnNextTile()
{
	
}

void ALevelGenerator::UnSpawnNextTile()
{

}

void ALevelGenerator::SpawnLastTile()
{

}

void ALevelGenerator::UnSpawnLastTile()
{

}

