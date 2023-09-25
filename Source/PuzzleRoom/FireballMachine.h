// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireballMachine.generated.h"

UCLASS()
class PUZZLEROOM_API AFireballMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireballMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire(float DeltaTime);

	UFUNCTION()
	void ThrowFireball();

private:

	float InitialCooldown = 0.f;

	UPROPERTY(EditAnywhere, Category = "Fireballs")
	float IgnitionPeriod = 5.f;

	UPROPERTY(EditAnywhere, Category = "Fireballs")
	float DestroyPeriod = 2.f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Fireballs")
	UStaticMeshComponent* MachineMesh;

	UPROPERTY(EditAnywhere, Category = "Fireballs", Meta = (MakeEditWidget = true))
	FVector BarrelOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Fireballs")
	TSubclassOf<class AFireball> FireballClass;

};
