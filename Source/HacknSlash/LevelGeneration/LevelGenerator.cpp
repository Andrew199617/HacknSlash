// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "LevelGenerator.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ALevelGenerator::ALevelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*FObjectInitializer* init = new FObjectInitializer();*/
	//Add Modules/MapPieces
	/*root = init->CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	SetRootComponent(root);

	lastModule = CreateStaticMeshComponent(init, TEXT("Left module"));
	currentModule = CreateStaticMeshComponent(init, TEXT("Current module"));
	nextModule = CreateStaticMeshComponent(init, TEXT("Next module"));


	RootComponent = root;*/

	

	curTile = 0;
}

UStaticMeshComponent* ALevelGenerator::CreateStaticMeshComponent(FObjectInitializer* init, FName moduleName)
{
	UStaticMeshComponent* modulueToAdd = nullptr;
	//modulueToAdd = init->CreateDefaultSubobject<UStaticMeshComponent>(this,moduleName);
	modulueToAdd = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this, "VFMesh");
	modulueToAdd->Mobility = EComponentMobility::Stationary;
	modulueToAdd->SetSimulatePhysics(false);
	modulueToAdd->SetupAttachment(RootComponent);
	modulueToAdd->bEditableWhenInherited = true;
	return modulueToAdd;
}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();

	world = GetWorld();

	if (world)
	{
		if (spawnableMeshes.Num() > 0)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = NULL;

			offset.Set(0, 0, 0);

			//create actors
			lastModule = world->SpawnActor<AStaticMeshActor>(module_1.Get(), FVector(0, 5000, 0), FRotator::ZeroRotator, spawnParams);
			lastModule->SetMobility(EComponentMobility::Movable);
			//
			currentModule = world->SpawnActor<AStaticMeshActor>(module_1.Get(), FVector(0, 0, 0), FRotator::ZeroRotator, spawnParams);
			currentModule->SetMobility(EComponentMobility::Movable);
			//
			nextModule = world->SpawnActor<AStaticMeshActor>(module_1.Get(), FVector(0, -5000, 0), FRotator::ZeroRotator, spawnParams);
			nextModule->SetMobility(EComponentMobility::Movable);
			//
		}
	}

	
}

// Called every frame
void ALevelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelGenerator::SpawnNextTile()
{
	if (world)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = NULL;

		curTile++;
		lastModule->SetActorLocation(FVector(0, curTile * -5000 - 5000 , 0));
		lastModule->GetStaticMeshComponent()->SetRelativeLocation(FVector(0, -10000, 0));
		lastModule->GetStaticMeshComponent()->SetStaticMesh(spawnableMeshes[0]);
		/*lastModule->Destroy();
		lastModule = currentModule;
		currentModule = nextModule;
		world->SpawnActor<AStaticMeshActor>(module_1.Get(), FVector(0, -10000, 0), FRotator::ZeroRotator, spawnParams);*/
	}

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

