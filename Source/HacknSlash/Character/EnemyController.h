// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class HACKNSLASH_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void Possess(APawn* InPawn) override;

private:
	class AHacknSlashCharacter* characterRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CustomAI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* behaviorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CustomAI", meta = (AllowPrivateAccess = "true"))
	UBlackboardData* blackboardData;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CustomAI", meta = (AllowPrivateAccess = "true"))
	UBlackboardComponent* blackboardComponent;
};
