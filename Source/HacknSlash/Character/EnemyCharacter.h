// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/BaseCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * Base Enemy Character
 */
UCLASS()
class HACKNSLASH_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	class AHacknSlashCharacter* characterRef;
	//class Weapon* weapon;
};
