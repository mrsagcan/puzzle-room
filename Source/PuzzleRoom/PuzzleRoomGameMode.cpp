// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleRoomGameMode.h"
#include "PuzzleRoomCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"

APuzzleRoomGameMode::APuzzleRoomGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;


}

void APuzzleRoomGameMode::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = Cast<APuzzleRoomCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (IsValid(PlayerPawn))
	{
		auto HealthComp = PlayerPawn->FindComponentByClass<UHealthComponent>();
		if (HealthComp)
		{
			HealthComp->OnPlayerDeath.AddUniqueDynamic(this, &APuzzleRoomGameMode::GameOver);
		}
	}
}

void APuzzleRoomGameMode::GameOver()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerPawn->DisableInput(PlayerController);
	FTimerHandle GameOverTimer;
	GetWorldTimerManager().SetTimer(GameOverTimer, this, &APuzzleRoomGameMode::RestartLevel, 2.f, false);

}

void APuzzleRoomGameMode::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
