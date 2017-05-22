// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "ShieldPickup.h"
#include "HacknSlashCharacter.h"

AShieldPickup::AShieldPickup() : ABasePickup()
{

}

void AShieldPickup::OnPickup(AActor* OtherActor)
{
	if (OtherActor->GetName() == playerCharacter->GetName())
	{
		playerCharacter->Recharge(shieldAmountInt);
	}
}

void AShieldPickup::BeginPlay()
{
	Super::BeginPlay();
	switch (shieldAmount)
	{
	case EShieldAmount::SMALL_SHIELD:
		shieldAmountInt = 33;
		break;
	case EShieldAmount::MEDIUM_SHIELD:
		shieldAmountInt = 66;
		break;
	case EShieldAmount::FULL_SHIELD:
		shieldAmountInt = 100;
		break;
	default:
		break;

	}
}
