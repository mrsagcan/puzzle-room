// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamagingObject.generated.h"

UCLASS()
class PUZZLEROOM_API ADamagingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamagingObject();

protected:
	
	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage;

	void GiveDamage();

};
