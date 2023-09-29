// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PuzzleRoomGameMode.generated.h"

UCLASS(minimalapi)
class APuzzleRoomGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APuzzleRoomGameMode();

	UFUNCTION()
	void GameOver();

	UFUNCTION()
	void RestartLevel();

protected:
	virtual void BeginPlay() override;

private:

	class APuzzleRoomCharacter* PlayerPawn;
};



