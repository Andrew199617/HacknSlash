// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "BTTask_MoveToPlayer.h"
#include "HacknSlashCharacter.h"
#include "Character/EnemyController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemyController* enemy = Cast<AEnemyController>(OwnerComp.GetAIOwner());

	AHacknSlashCharacter* characterRef = Cast<AHacknSlashCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player"));

	if (characterRef)
	{
		enemy->MoveToActor(characterRef, 5.f);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
