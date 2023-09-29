// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Root Collision"));
	RootComponent = SphereComponent;
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SphereComponent);

	TeleportLocation.Set(0, 0, 0);
}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	
	SetTeleportLocation();
}

void ATeleporter::SetTeleportLocation()
{
	TArray<AActor*> StartPoints;
	auto ClassToFind = APlayerStart::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, StartPoints);
	if (!StartPoints.IsEmpty())
	{
		TeleportLocation = StartPoints[0]->GetActorLocation();
	}
}

// Called every frame
void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATeleporter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == UGameplayStatics::GetPlayerPawn(this, 0) && !TeleportLocation.IsZero())
	{
		OtherActor->SetActorLocation(TeleportLocation, false);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *TeleportLocation.ToString());
		GetWorld()->TimeSeconds = 0.f;
	}
}