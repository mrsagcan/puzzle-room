// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagingObject.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleRoomCharacter.h"

// Sets default values
ADamagingObject::ADamagingObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADamagingObject::GiveDamage()
{
	if (const auto PlayerChar = Cast<APuzzleRoomCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		PlayerChar->ApplyDamage(Damage);
	}
}

