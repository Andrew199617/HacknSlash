// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SpawnConfiguration.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKNSLASH_API USpawnConfiguration : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnConfiguration();

	TArray<AStaticMeshActor*> spawns;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetLocation(FVector NewLocation);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns", meta = (AllowPrivateAccess = "true"))
	int numSpawns;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns", meta = (AllowPrivateAccess = "true"))
	FVector spawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEnemyCharacter> spawnableEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* spawnMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawns", meta = (AllowPrivateAccess = "true"))
	float spawnEvery;
	
	//AEnemyCharacter* spawnedEnemies[24];
};
