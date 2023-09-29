// Fill out your copyright notice in the Description page of Project Settings.

#include "Fireball.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFireball::AFireball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComp->InitSphereRadius(15.0f);
	RootComponent = CollisionComp;
	CollisionComp->OnComponentHit.AddDynamic(this, &AFireball::OnHit);


	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComp->SetUpdatedComponent(CollisionComp);
	ProjectileMovementComp->bRotationFollowsVelocity = true;


	ProjectileMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
	ProjectileMeshComp->SetupAttachment(RootComponent);


	InitialLifeSpan = 2.f;

}

// Called when the game starts or when spawned
void AFireball::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFireball::ThrowToDirection(const FVector& ShootDirection)
{
	ProjectileMovementComp->Velocity = ShootDirection;
	OnFireballSpawned.Broadcast(FireTrail, CollisionComp);
}

void AFireball::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this)
	{
		if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("Player is hit by fireball."));
			GiveDamage();
		}
		Destroy();
	}
}