// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "ColliderGenerator.h"


// Sets default values for this component's properties
UColliderGenerator::UColliderGenerator()
{
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Colliders"));
	root->bEditableWhenInherited = true;

	topCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Top Collider"));
	SetupCollider(topCollider);

	botCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Bot Collider"));
	SetupCollider(botCollider);

	sidewalkOffset = 0;
}

void UColliderGenerator::OnConstruction(const FTransform& Transform)
{
	if (root)
	{
		root->SetRelativeTransform(Transform);
		topCollider->SetRelativeLocation(FVector(sidewalkOffset - 500, 0, 0));
		botCollider->SetRelativeLocation(FVector(sidewalkOffset + 500, 0, 0));
		topCollider->SetRelativeScale3D(FVector(.2f, 75, 10));
		botCollider->SetRelativeScale3D(FVector(.2f, 75, 10));
	}
}

void UColliderGenerator::SetRelativeLocation(FVector newLocation)
{
	root->SetRelativeLocation(newLocation);
}

void UColliderGenerator::SetupCollider(UBoxComponent* mesh)
{
	mesh->SetupAttachment(root);
	mesh->Mobility = EComponentMobility::Movable;
	mesh->bGenerateOverlapEvents = false;
	mesh->SetCollisionProfileName(TEXT("InvisibleWall"));
	mesh->bEditableWhenInherited = true;
	mesh->CastShadow = false;
	mesh->bHiddenInGame = true;
	mesh->SetBoxExtent(FVector(100, 100, 100), false);
	mesh->RegisterComponent();
}

void UColliderGenerator::BeginPlay()
{
	topCollider->SetRelativeLocation(FVector(sidewalkOffset - 500, 0, 0));
	botCollider->SetRelativeLocation(FVector(sidewalkOffset + 500, 0, 0));
}

