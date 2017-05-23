// Fill out your copyright notice in the Description page of Project Settings.

#include "HacknSlash.h"
#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter() : ACharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	maxShield = 100;
	maxHP = 100;
	health = maxHP;
	shield = maxShield;
}

void ABaseCharacter::RecieveDamage(int Damage)
{

	if (Damage > 0) {
		if (shield > 0)
		{
			if (Damage < shield) {
				shield -= Damage;
			}
			else {
				Damage -= shield; 
				shield = 0; 
				health -= Damage;
			}
		}
		else {
			health -= Damage;
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Dealing negative damage."));
	}
}

void ABaseCharacter::Heal(int Amount)
{
	if (Amount > 0)
	{
		health += Amount;
		health = FMath::Clamp<float>(health, 0.0f, maxHP);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Healing negative damage."));
	}
}

void ABaseCharacter::Recharge(int Amount)
{
	if (Amount > 0)
	{
		shield += Amount;
		shield = FMath::Clamp<float>(shield, 0.0f, maxShield);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Healing negative damage."));
	}
}

int ABaseCharacter::GetMaxHP() const
{
	return maxHP;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
