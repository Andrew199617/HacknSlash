// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ColliderGenerator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKNSLASH_API UColliderGenerator : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UColliderGenerator();

	void OnConstruction(const FTransform& Transform, int maxTiles);

	void SetRelativeLocation(FVector newLocation);

public:
	USceneComponent* root;

	UBoxComponent* topCollider;

	UBoxComponent* botCollider;

private:
	void SetupCollider(UBoxComponent* mesh);

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider Generation", meta = (AllowPrivateAccess = "true"))
	float sidewalkOffset;
};
