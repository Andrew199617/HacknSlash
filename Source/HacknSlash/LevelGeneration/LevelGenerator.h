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

private:
	UStaticMeshComponent* CreateStaticMeshComponent(FObjectInitializer* init, FName moduleName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnNextTile();

	void UnSpawnNextTile();

	void SpawnLastTile();

	void UnSpawnLastTile();

	//Scene Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	AStaticMeshActor* lastModule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	AStaticMeshActor* currentModule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	AStaticMeshActor* nextModule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	AStaticMeshActor* added;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AStaticMeshActor> module_1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> spawnableMeshes;

	//Level Generation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	float numTiles;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	float curTile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	FVector offset;

	UWorld* world;
};
