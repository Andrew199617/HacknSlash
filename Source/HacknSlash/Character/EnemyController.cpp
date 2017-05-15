// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "EnemyController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "HacknSlashCharacter.h"

AEnemyController::AEnemyController() : AAIController()
{
	blackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	characterRef = Cast<AHacknSlashCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	if (blackboardData && blackboardComponent)
	{
		blackboardComponent->InitializeBlackboard(*blackboardData);
		UseBlackboard(blackboardData, blackboardComponent);

		int playerID = blackboardData->GetKeyID("Player");
		blackboardComponent->SetValueAsObject(blackboardData->GetKeyName(playerID), characterRef);
		int targetLocationID = blackboardData->GetKeyID("PlayerLocation");
		if (characterRef)
		{
			blackboardComponent->SetValueAsVector(blackboardData->GetKeyName(targetLocationID), characterRef->GetActorLocation());
		}

		if (behaviorTree)
		{
			RunBehaviorTree(behaviorTree);
		}
		
	}

}
