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

	health = 100;
}

void ABaseCharacter::TakeDamage(int Damage)
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
