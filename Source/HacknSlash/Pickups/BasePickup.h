// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

UCLASS()
class HACKNSLASH_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnPickup();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
protected:
	static class AHacknSlashCharacter* playerCharacter;

	USphereComponent* collider;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float pickupRadius;
	

};
