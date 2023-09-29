// Fill out your copyright notice in the Description page of Project Settings.


#include "FPPlayerController.h"
#include "Blueprint/UserWidget.h"

AFPPlayerController::AFPPlayerController()
{

}

void AFPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AddWidgetToViewport(HUDClass);
}

void AFPPlayerController::AddWidgetToViewport(TSubclassOf<UUserWidget> WidgetClass)
{
	UUserWidget* Screen = CreateWidget(this, WidgetClass);
	if (Screen)
	{
		Screen->AddToViewport();
	}
}