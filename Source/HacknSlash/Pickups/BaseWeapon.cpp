// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "BaseWeapon.h"




ABaseWeapon::ABaseWeapon() : ABasePickup()
{
	bShouldDestroy = false;
}

void ABaseWeapon::OnPickup(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Pickup Weapon"));
}
