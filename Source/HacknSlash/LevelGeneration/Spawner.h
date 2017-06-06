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

	TArray<class AEnemyCharacter*> spawnedEnemies;

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* myMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEnemyCharacter> enemyToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns", meta = (AllowPrivateAccess = "true"))
	float spawnEvery;

private:
	bool spawnRadius;
};
