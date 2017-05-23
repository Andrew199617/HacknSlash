// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "HealthPack.h"
#include "HacknSlashCharacter.h"

AHealthPack::AHealthPack() : ABasePickup()
{

}

void AHealthPack::OnPickup(AActor* OtherActor)
{
	if (OtherActor->GetName() == playerCharacter->GetName())
	{
		playerCharacter->Heal(healAmountInt);
	}
}

void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
	switch (healAmount)
	{
	case EHealAmount::SMALL_HEALTH_PACK:
		healAmountInt = 25;
		break;
	case EHealAmount::MEDIUM_HEALTH_PACK:
		healAmountInt = 50;
		break;
	case EHealAmount::LARGE_HEALTH_PACK:
		healAmountInt = 75;
		break;
	case EHealAmount::FULL_HEAL:
		healAmountInt = 100;
		break;
	default:
		break;

	}
}
