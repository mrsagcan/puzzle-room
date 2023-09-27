// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MovePlatformComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEROOM_API UMovePlatformComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovePlatformComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	FVector StartLocation;
	FVector EndLocation;
	float ElapsedTime = 0.f;
	float ElapsedWaitTime = 0.f;

	UPROPERTY(EditAnywhere, Category = "Lerp")
	float LerpDuration = 5.f;

	UPROPERTY(EditAnywhere, Category = "Lerp")
	float WaitDuration = 3.f;

	UPROPERTY(EditAnywhere, Category = "Lerp", Meta = (MakeEditWidget = "true"))
	FVector TargetOffset;

	void MovePlatform(float DeltaTime);
	void UpdateEndLocation();
};
