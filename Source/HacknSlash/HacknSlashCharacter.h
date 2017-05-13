// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Character/BaseCharacter.h"
#include "HacknSlashCharacter.generated.h"

UCLASS(config=Game)
class AHacknSlashCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	/** Called for side to side input */
	void MoveRight(float Speed);

	/** Called for Forward to Backwards input */
	void MoveForward(float Speed);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	AHacknSlashCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "HUD")
	class UUserWidget* Hud() const { return hud; }

	UFUNCTION(BlueprintCallable, Category = "HUD")
	class UUserWidget* SetHud(class UUserWidget* val);

private:
	class UUserWidget* hud;
	
	
};
