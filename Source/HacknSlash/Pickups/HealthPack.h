// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickups/BasePickup.h"
#include "HealthPack.generated.h"

UENUM(BlueprintType)
enum class EHealAmount : uint8 {
	SMALL_HEALTH_PACK UMETA(DisplayName = "Small"),
	MEDIUM_HEALTH_PACK UMETA(DisplayName = "Medium"),
	LARGE_HEALTH_PACK UMETA(DisplayName = "Large"),
	FULL_HEAL UMETA(DisplayName = "Full")
};

/**
 * 
 */
UCLASS()
class HACKNSLASH_API AHealthPack : public ABasePickup
{
	GENERATED_BODY()
	
public:
	AHealthPack();

	virtual void OnPickup(AActor* OtherActor) override;

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EHealAmount healAmount;
	int healAmountInt;
};
