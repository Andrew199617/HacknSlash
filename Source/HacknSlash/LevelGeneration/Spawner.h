// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class HACKNSLASH_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	int curEnemy;

	int maxEnemies;

	class UClass* enemyClass;

	TArray<class AEnemyCharacter*> spawnedEnemies;

	void MyBeginPlay();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* myMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns", meta = (AllowPrivateAccess = "true"))
	float spawnEvery;
};
