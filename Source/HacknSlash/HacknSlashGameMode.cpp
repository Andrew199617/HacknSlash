// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "HacknSlash.h"
#include "HacknSlashGameMode.h"
#include "HacknSlashCharacter.h"

AHacknSlashGameMode::AHacknSlashGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
