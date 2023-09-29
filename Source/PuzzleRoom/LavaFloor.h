// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamagingObject.h"
#include "LavaFloor.generated.h"

UCLASS()
class PUZZLEROOM_API ALavaFloor : public ADamagingObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALavaFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void CalculateDamageTime(AActor* OtherActor);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	class UBoxComponent* BoxComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	class UBoxComponent* OutBoxComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Damage Timer")
	float CallRate = 3.f;
	
	FTimerHandle LavaDamageTimer;
	FTimerDelegate LavaDamageTimerDel;
};
