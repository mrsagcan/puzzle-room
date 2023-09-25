// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleRoomGameMode.h"
#include "PuzzleRoomCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuzzleRoomGameMode::APuzzleRoomGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
