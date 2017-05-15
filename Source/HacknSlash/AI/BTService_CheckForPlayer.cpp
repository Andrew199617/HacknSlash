// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "BTService_CheckForPlayer.h"
#include "HacknSlashCharacter.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"

UBTService_CheckForPlayer::UBTService_CheckForPlayer()
{
	bCreateNodeInstance = true;
}

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AHacknSlashCharacter* characterRef = Cast<AHacknSlashCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (characterRef)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject("Player", characterRef);
	}
}
