// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

UCLASS(BlueprintType, Blueprintable)
class HACKNSLASH_API ALevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	void SpawnNextTile();

	void SpawnLastTile();

	void SetCurTile(int tile);

private:
	//Called to add modules as a subcomponent
	void InitializeModules();

	//Called to set initial Module Data
	void SetupModule(UStaticMeshComponent* mesh);

	//Called to add Colliders that will spawn the next tile.
	void SpawnColliders();

	//Called to add Spawns for enemies to level.
	void InitializeSpawns();

	void SetModuleGeneratorLocations(FVector newLocation);

public:
	//Modules
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Modules", meta = (AllowPrivateAccess = "true"))
	USceneComponent* modulesRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modules", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* lastModule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modules", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* currentModule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modules", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* nextModule;

	//Generators
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Colliders", meta = (AllowPrivateAccess = "true"))
	class ANewLevelCollider* LastModuleGenerator;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Colliders", meta = (AllowPrivateAccess = "true"))
	class ANewLevelCollider* nextModuleGenerator;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NavMesh", meta = (AllowPrivateAccess = "true"))
	class ANavMeshBoundsVolume* navMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawns", meta = (AllowPrivateAccess = "true"))
	USceneComponent* spawns;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Colliders", meta = (AllowPrivateAccess = "true"))
	class UColliderGenerator* colliders;

	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> spawnableMeshes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* colliderMesh;

	//Level Generation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	float maxTiles;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	float curTile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	float moduleWidth;

};
