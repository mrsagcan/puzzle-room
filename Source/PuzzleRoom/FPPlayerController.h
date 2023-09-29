// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEROOM_API AFPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AFPPlayerController();

protected:

	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> HUDClass;

	void AddWidgetToViewport(TSubclassOf<UUserWidget> WidgetClass);
};
