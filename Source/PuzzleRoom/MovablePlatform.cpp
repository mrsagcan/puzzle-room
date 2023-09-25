// Fill out your copyright notice in the Description page of Project Settings.


#include "MovablePlatform.h"
#include "Components/BoxComponent.h"
#include "MovePlatformComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AMovablePlatform::AMovablePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxComp;
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AMovablePlatform::OnOverlapBegin);

	MovingPlatform = CreateDefaultSubobject<UMovePlatformComponent>(TEXT("Movement Component"));
	MovingPlatform->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMovablePlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovablePlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, DustEffect, GetActorLocation());
}

