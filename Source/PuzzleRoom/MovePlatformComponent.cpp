// Fill out your copyright notice in the Description page of Project Settings.


#include "MovePlatformComponent.h"

// Sets default values for this component's properties
UMovePlatformComponent::UMovePlatformComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UMovePlatformComponent::BeginPlay()
{
	Super::BeginPlay();

	UpdateEndLocation();
}


// Called every frame
void UMovePlatformComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Waits for some time between movements.
	if (ElapsedWaitTime > 0)
	{
		ElapsedWaitTime -= DeltaTime;
	}
	else
	{
		MovePlatform(DeltaTime);
	}
}

void UMovePlatformComponent::MovePlatform(float DeltaTime)
{
	if (ElapsedTime < LerpDuration)
	{
		GetOwner()->SetActorLocation(FMath::Lerp(StartLocation, EndLocation, ElapsedTime / LerpDuration));
		ElapsedTime += DeltaTime;
	}
	else
	{
		TargetOffset = -TargetOffset;
		UpdateEndLocation();
	}
}

void UMovePlatformComponent::UpdateEndLocation()
{
	ElapsedTime = 0;
	StartLocation = GetOwner()->GetActorLocation();
	EndLocation = StartLocation + TargetOffset * GetOwner()->GetActorScale();
	ElapsedWaitTime = WaitDuration;
}

