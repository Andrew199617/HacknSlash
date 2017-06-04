// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "LevelGenerator.h"
#include "Components/StaticMeshComponent.h"
#include "NewLevelCollider.h"
#include "ColliderGenerator.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "SpawnConfiguration.h"
#include <ctime> 
#include <string> 

// Sets default values
ALevelGenerator::ALevelGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	InitializeModules();

	spawnConfiguration = CreateDefaultSubobject<USpawnConfiguration>(TEXT("Spawn Configuration"));
	AddOwnedComponent(spawnConfiguration);

	colliders = CreateDefaultSubobject<UColliderGenerator>(TEXT("Collider Generator"));
	AddOwnedComponent(colliders);
	colliders->root->SetupAttachment(RootComponent);
	colliders->root->RegisterComponent();
	
	InitializeSpawns();

	navMeshDisplay = CreateDefaultSubobject<UBoxComponent>(TEXT("Nav Mesh Display"));
	navMeshDisplay->SetupAttachment(RootComponent);
	navMeshDisplay->SetBoxExtent(FVector(100, 100, 100), false);
	navMeshDisplay->RegisterComponent();

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
		UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());
		NavSys->OnNavigationBoundsUpdated(navMesh);
		navMesh->SetActorScale3D(navMeshDisplay->GetRelativeTransform().GetScale3D());
		navMesh->SetActorLocation(navMeshDisplay->GetRelativeTransform().GetLocation() + GetActorLocation());
		navMesh->GetBrushComponent()->Mobility = EComponentMobility::Movable;
		navMeshDisplay->DestroyComponent();
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

		currentModule->SetStaticMesh(spawnableMeshes[1]);
		currentModule->SetRelativeLocation(transLoc);

		nextModule->SetStaticMesh(spawnableMeshes[2]);
		nextModule->SetRelativeLocation(FVector(0, -moduleWidth, 0) + transLoc);

		navMeshDisplay->SetRelativeLocation(navMeshDisplay->GetRelativeTransform().GetLocation() + transLoc);
	}
	colliders->OnConstruction(Transform);
}

void ALevelGenerator::SpawnNextTile()
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
	modulesRoot->SetupAttachment(RootComponent);
	modulesRoot->RegisterComponent();

	lastModule = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Last Module"));
	SetupModule(lastModule);
	currentModule = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Current Module"));
	SetupModule(currentModule);
	nextModule = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Next Module"));
	SetupModule(nextModule);
}

void ALevelGenerator::SetupModule(UStaticMeshComponent* mesh)
{
	mesh->Mobility = EComponentMobility::Movable;
	mesh->bGenerateOverlapEvents = false;
	mesh->bEditableWhenInherited = true;
	mesh->SetupAttachment(modulesRoot);
	mesh->RegisterComponent();
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
	
}

void ALevelGenerator::SetModuleGeneratorLocations(FVector newLocation)
{
	LastModuleGenerator->SetActorLocation(FVector(1200, moduleWidth - (moduleWidth / 2), 0) + newLocation);
	nextModuleGenerator->SetActorLocation(FVector(1200, -moduleWidth / 2, 0) + newLocation);
}

