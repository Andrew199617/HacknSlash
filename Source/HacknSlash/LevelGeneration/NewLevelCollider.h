// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "NewLevelCollider.generated.h"

/**
 * 
 */
UCLASS()
class HACKNSLASH_API ANewLevelCollider : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANewLevelCollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	class AHacknSlashCharacter* characterRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LevelGeneration", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ALevelGenerator> levelGenerator;

	class ALevelGenerator* levelGeneratorRef;
};
