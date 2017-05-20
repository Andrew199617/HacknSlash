// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class HACKNSLASH_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RecieveDamage(int Damage);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Heal(int Amount);

	UFUNCTION(BlueprintPure, Category = "Stats")
	int GetMaxHP() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float shield;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int ammo;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int maxHP;

};
