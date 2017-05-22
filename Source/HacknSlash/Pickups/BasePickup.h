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

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called when the player collides with this
	virtual void OnPickup(AActor* OtherActor);

	void DestroySafe();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;

protected:

	class AHacknSlashCharacter* playerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USphereComponent* collider;

	/************************************************************************/
	/* Will the pickup be destroyed when its walked over.*/
	/************************************************************************/
	bool bShouldDestroy;

private:

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float pickupRadius;
	

};
