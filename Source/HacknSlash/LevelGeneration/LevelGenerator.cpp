// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "LevelGenerator.h"
#include "Components/StaticMeshComponent.h"
#include "NewLevelCollider.h"
#include "ColliderGenerator.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"


// Sets default values
ALevelGenerator::ALevelGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	InitializeModules();
	colliders = CreateDefaultSubobject<UColliderGenerator>(TEXT("Collider Generator"));
	AddOwnedComponent(colliders);
	colliders->root->SetupAttachment(RootComponent);

	InitializeSpawns();

	curTile = 0;
	moduleWidth = 5000;
	maxTiles = 10;
}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();

	SpawnColliders();
	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

		navMesh = world->SpawnActor<ANavMeshBoundsVolume>(spawnParams);
		navMesh->SetActorScale3D(FVector(10, 150, 10));
		world->GetNavigationSystem()->OnNavigationBoundsUpdated(navMesh);
	}
}

void ALevelGenerator::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (spawnableMeshes.Num() > 0)
	{
		FVector transLoc = Transform.GetLocation();
		lastModule->SetStaticMesh(spawnableMeshes[0]);
		lastModule->SetRelativeLocation(FVector(0, moduleWidth, 0) + transLoc);
		currentModule->SetStaticMesh(spawnableMeshes[0]);
		currentModule->SetRelativeLocation(FVector(0, 0, 0) + transLoc);
		nextModule->SetStaticMesh(spawnableMeshes[0]);
		nextModule->SetRelativeLocation(FVector(0, -moduleWidth, 0) + transLoc);
	}
	colliders->OnConstruction(Transform);
}

void ALevelGenerator::SpawnNextTile()
{
	if (curTile < maxTiles)
	{
		curTile++;

		lastModule->SetRelativeLocation(FVector(0, curTile * -moduleWidth - moduleWidth, 0));
		lastModule->SetStaticMesh(spawnableMeshes[0]);

		UStaticMeshComponent* temp = lastModule;
		lastModule = currentModule;
		currentModule = nextModule;
		nextModule = temp;

		FVector newLocation = FVector(0, curTile * -moduleWidth, 0);
		colliders->SetRelativeLocation(newLocation);
		navMesh->SetActorLocation(newLocation + GetActorLocation());
		SetModuleGeneratorLocations(newLocation + GetActorLocation());
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("End of level reached"));
	}

}

void ALevelGenerator::SpawnLastTile()
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
		SetModuleGeneratorLocations(newLocation + GetActorLocation());
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("End of level reached"));
	}
}

void ALevelGenerator::SetCurTile(int tile)
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

void ALevelGenerator::InitializeModules()
{
	modulesRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Modules"));
	modulesRoot->RegisterComponent();
	modulesRoot->SetupAttachment(RootComponent);

	lastModule = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Last Module"));
	SetupModule(lastModule);
	currentModule = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Current Module"));
	SetupModule(currentModule);
	nextModule = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Next Module"));
	SetupModule(nextModule);
}

void ALevelGenerator::SetupModule(UStaticMeshComponent* mesh)
{
	mesh->RegisterComponent();
	mesh->Mobility = EComponentMobility::Movable;
	mesh->bGenerateOverlapEvents = false;
	mesh->bEditableWhenInherited = true;
	mesh->SetupAttachment(modulesRoot);
}

void ALevelGenerator::SpawnColliders()
{
	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

		LastModuleGenerator = world->SpawnActor<ANewLevelCollider>(spawnParams);
		nextModuleGenerator = world->SpawnActor<ANewLevelCollider>(spawnParams);

		LastModuleGenerator->GetStaticMeshComponent()->SetStaticMesh(colliderMesh);
		nextModuleGenerator->GetStaticMeshComponent()->SetStaticMesh(colliderMesh);

		LastModuleGenerator->SetLevelGeneratorRef(this);
		nextModuleGenerator->SetLevelGeneratorRef(this);

		LastModuleGenerator->SetActorLocation(FVector(1200, moduleWidth - (moduleWidth / 2), 0));
		nextModuleGenerator->SetActorLocation(FVector(1200, -moduleWidth / 2, 0));
	}
}

void ALevelGenerator::InitializeSpawns()
{
	spawns = CreateDefaultSubobject<USceneComponent>(TEXT("Spawns"));
	spawns->SetupAttachment(RootComponent);
}

void ALevelGenerator::SetModuleGeneratorLocations(FVector newLocation)
{
	LastModuleGenerator->SetActorLocation(FVector(1200, moduleWidth - (moduleWidth / 2), 0) + newLocation);
	nextModuleGenerator->SetActorLocation(FVector(1200, -moduleWidth / 2, 0) + newLocation);
}

