// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DamagingObject.h"
#include "LavaGeyser.generated.h"

UCLASS()
class PUZZLEROOM_API ALavaGeyser : public ADamagingObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALavaGeyser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void BlowGeyser();

	UFUNCTION()
	void ExtinctGeyser(UNiagaraComponent* PSystem);

private:

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	class USphereComponent* SphereComp;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float BurstRate = 2.f;

	UPROPERTY(EditAnywhere, Category = "Fire")
	class UNiagaraSystem* BurstEffect;

	UPROPERTY(EditAnywhere, Category = "Fire")
	FVector BurstLocation;

	FTimerHandle BurstTimer;
};
