// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "LevelGeneration2.h"
#include "Components/StaticMeshComponent.h"
#include "NewLevelCollider.h"
#include "ColliderGenerator.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "SpawnConfiguration.h"
#include <ctime> 
#include <string> 

// Sets default values
ALevelGeneration2::ALevelGeneration2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	moduleWidth = 5000;
	maxTiles = 7;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	InitializeModules();

	spawnConfiguration = CreateDefaultSubobject<USpawnConfiguration>(TEXT("Spawn Configuration"));
	AddOwnedComponent(spawnConfiguration);

	colliders = CreateDefaultSubobject<UColliderGenerator>(TEXT("Collider Generator"));
	AddOwnedComponent(colliders);
	colliders->root->SetupAttachment(RootComponent);
	colliders->root->RegisterComponent();

	InitializeSpawns();

}

// Called when the game starts or when spawned
void ALevelGeneration2::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

	}
}

void ALevelGeneration2::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (spawnableMeshes.Num() > 0)
	{
		FVector transLoc = Transform.GetLocation();

		if (spawnableMeshes.Num() > 2 && spawnableMeshOffsets.Num() > 2)
		{
			lastModule->SetStaticMesh(spawnableMeshes[0]);
			lastModule->SetRelativeLocation(FVector(0, moduleWidth, 0) + transLoc + spawnableMeshOffsets[0]);

			currentModule->SetStaticMesh(spawnableMeshes[1]);
			currentModule->SetRelativeLocation(transLoc + spawnableMeshOffsets[1]);

			nextModule->SetStaticMesh(spawnableMeshes[2]);
			nextModule->SetRelativeLocation(FVector(0, -moduleWidth, 0) + transLoc + spawnableMeshOffsets[2]);

			srand((unsigned)time(0));
			for (int i = 0; i < maxTiles; ++i)
			{
				int random_integer = rand() % spawnableMeshes.Num();
				meshes[i]->SetStaticMesh(spawnableMeshes[random_integer]);
				FVector newLocation = (spawnableMeshOffsets.Num() > i + 3) ? FVector(0, -((i + 2) * moduleWidth), 0) + transLoc + spawnableMeshOffsets[i + 3] : FVector(0, -((i + 2) * moduleWidth), 0) + transLoc;
				nextModule->SetRelativeLocation(newLocation);
			}
		}

	}
	colliders->OnConstruction(Transform);
}

void ALevelGeneration2::SpawnNextTile()
{
	if (curTile < maxTiles)
	{
		curTile++;

		lastModule->SetRelativeLocation(FVector(0, curTile * -moduleWidth - moduleWidth, 0));
		srand((unsigned)time(0));
		int random_integer = rand() % spawnableMeshes.Num();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, std::to_string(random_integer).c_str());

		lastModule->SetStaticMesh(spawnableMeshes[random_integer]);

		UStaticMeshComponent* temp = lastModule;
		lastModule = currentModule;
		currentModule = nextModule;
		nextModule = temp;

		FVector newLocation = FVector(0, curTile * -moduleWidth, 0);
		colliders->SetRelativeLocation(newLocation);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("End of level reached"));
	}

}

void ALevelGeneration2::SpawnLastTile()
{
	if (curTile > 0)
	{
		curTile--;

		nextModule->SetRelativeLocation(FVector(0, curTile * -moduleWidth + moduleWidth, 0));
		nextModule->SetStaticMesh(spawnableMeshes[0]);

		UStaticMeshComponent* temp = nextModule;
		nextModule = currentModule;
		currentModule = lastModule;
		lastModule = temp;

		FVector newLocation = FVector(0, curTile * -moduleWidth, 0);
		colliders->SetRelativeLocation(newLocation);
		navMesh->SetActorLocation(newLocation + GetActorLocation());
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("End of level reached"));
	}
}

void ALevelGeneration2::SetCurTile(int tile)
{
	if (tile < 0 || tile >= maxTiles)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Could not set tile."));
		return;
	}
	curTile = tile;

	lastModule->SetRelativeLocation(FVector(0, curTile * -moduleWidth + moduleWidth, 0));
	currentModule->SetRelativeLocation(FVector(0, curTile * -moduleWidth, 0));
	nextModule->SetRelativeLocation(FVector(0, curTile * -moduleWidth - moduleWidth, 0));
}

void ALevelGeneration2::InitializeModules()
{
	modulesRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Modules"));
	modulesRoot->SetupAttachment(RootComponent);
	modulesRoot->RegisterComponent();

	lastModule = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Last Module"));
	SetupModule(lastModule);
	currentModule = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Current Module"));
	SetupModule(currentModule);
	nextModule = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Next Module"));
	SetupModule(nextModule);

	for (int i = 0; i < maxTiles; ++i)
	{
		meshes[i] = CreateDefaultSubobject<UStaticMeshComponent>(("Module" + std::to_string(i)).c_str());
		SetupModule(meshes[i]);
	}
}

void ALevelGeneration2::SetupModule(UStaticMeshComponent* mesh)
{
	mesh->Mobility = EComponentMobility::Movable;
	mesh->bGenerateOverlapEvents = false;
	mesh->bEditableWhenInherited = true;
	mesh->SetupAttachment(modulesRoot);
	mesh->RegisterComponent();
}

void ALevelGeneration2::InitializeSpawns()
{

}

