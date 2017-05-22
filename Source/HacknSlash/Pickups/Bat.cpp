// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "Bat.h"




ABat::ABat() : ABaseWeapon()
{

}

void ABat::OnPickup(AActor* OtherActor)
{
	collider->Deactivate();
}

void ABat::BeginPlay()
{
	Super::BeginPlay();
}
