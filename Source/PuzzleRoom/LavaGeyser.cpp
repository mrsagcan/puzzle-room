// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaGeyser.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ALavaGeyser::ALavaGeyser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = SphereComp;
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ALavaGeyser::OnBeginOverlap);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALavaGeyser::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(BurstTimer, this, &ALavaGeyser::BlowGeyser, BurstRate, true);

}

// Called every frame
void ALavaGeyser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALavaGeyser::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is hit by lava particles."));
		GiveDamage();
	}
}

void ALavaGeyser::BlowGeyser()
{
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	auto NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, BurstEffect, GetActorLocation());
	NiagaraComp->OnSystemFinished.AddDynamic(this, &ALavaGeyser::ExtinctGeyser);
}


void ALavaGeyser::ExtinctGeyser(UNiagaraComponent* PSystem)
{
	SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
