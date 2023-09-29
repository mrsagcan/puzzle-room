// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "PuzzleRoomCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	if (const auto PlayerChar = Cast<APuzzleRoomCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		PlayerChar->OnAppliedDamage.AddUniqueDynamic(this, &UHealthComponent::DamageTaken);
	}

	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(float Damage)
{
	if (Damage <= 0.f)	return;

	Health -= Damage;
	if (Health <= 0.f)
	{
		//TODO: Player DEAD
		OnPlayerDeath.Broadcast();
	}
	UE_LOG(LogTemp, Warning, TEXT("Player Health: %f"), Health);
}

float UHealthComponent::GetHealthPercent()
{
	return Health / MaxHealth;
}