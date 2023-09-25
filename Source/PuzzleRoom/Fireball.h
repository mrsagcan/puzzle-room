// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fireball.generated.h"

UCLASS()
class PUZZLEROOM_API AFireball : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireball();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ThrowToDirection(const FVector& ShootDirection);

	float GetDamage();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:

	UPROPERTY(EditAnywhere, Category = "Fireball")
	float Damage = 30.f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Fireball")
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Fireball")
	class UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Fireball")
	UStaticMeshComponent* ProjectileMeshComp;



};
