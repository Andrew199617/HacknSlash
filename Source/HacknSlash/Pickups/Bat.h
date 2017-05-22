// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickups/BaseWeapon.h"
#include "Bat.generated.h"

/**
 * 
 */
UCLASS()
class HACKNSLASH_API ABat : public ABaseWeapon
{
	GENERATED_BODY()

public:
	ABat();

	virtual void OnPickup(AActor* OtherActor) override;

	virtual void BeginPlay() override;

};
