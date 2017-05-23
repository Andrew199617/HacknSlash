// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickups/BasePickup.h"
#include "ShieldPickup.generated.h"

UENUM(BlueprintType)
enum class EShieldAmount : uint8 {
	SMALL_SHIELD UMETA(DisplayName = "Small"),
	MEDIUM_SHIELD UMETA(DisplayName = "Medium"),
	FULL_SHIELD UMETA(DisplayName = "Full")
};

/**
 * Base Class for all ShieldPickups.
 */
UCLASS()
class HACKNSLASH_API AShieldPickup : public ABasePickup
{
	GENERATED_BODY()

public:
	AShieldPickup();

	virtual void OnPickup(AActor* OtherActor) override;

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EShieldAmount shieldAmount;

	int shieldAmountInt;
};
