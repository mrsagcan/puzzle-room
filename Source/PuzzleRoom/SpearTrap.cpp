// Fill out your copyright notice in the Description page of Project Settings.


#include "SpearTrap.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpearTrap::ASpearTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = BoxComp;
	BoxComp->OnComponentHit.AddDynamic(this, &ASpearTrap::OnHit);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BoxComp);


}

// Called when the game starts or when spawned
void ASpearTrap::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ASpearTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASpearTrap::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Player is hit by spears."));
	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is hit by spears."));
		GiveDamage();
	}
}

