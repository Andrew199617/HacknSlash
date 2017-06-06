// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LevelGeneration2.generated.h"

UCLASS(BlueprintType, Blueprintable)
class HACKNSLASH_API ALevelGeneration2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGeneration2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

private:
	//Called to add modules as a subcomponent
	void InitializeModules();

	//Called to set initial Module Data
	void SetupModule(UStaticMeshComponent* mesh);

	//Called to add Spawns for enemies to level.
	void InitializeSpawns();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Configuration", meta = (AllowPrivateAccess = "true"))
	class USpawnConfiguration* spawnConfiguration;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Colliders", meta = (AllowPrivateAccess = "true"))
	class UColliderGenerator* colliders;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> spawnableMeshes;

	TArray<UStaticMeshComponent*> meshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	TArray<FVector> spawnableMeshOffsets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* colliderMesh;

	//Level Generation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	float maxTiles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	float moduleWidth;

};
