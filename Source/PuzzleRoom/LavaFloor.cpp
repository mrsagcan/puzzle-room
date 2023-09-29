// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaFloor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALavaFloor::ALavaFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxComp;
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ALavaFloor::OnOverlapBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ALavaFloor::OnOverlapEnd);

	OutBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Out Collider"));
	OutBoxComp->SetupAttachment(BoxComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lava Mesh"));
	Mesh->SetupAttachment(BoxComp);

}

// Called when the game starts or when spawned
void ALavaFloor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALavaFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALavaFloor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is overlapping."));
		if (GetWorldTimerManager().IsTimerActive(LavaDamageTimer))
		{
			GetWorldTimerManager().UnPauseTimer(LavaDamageTimer);
		}
		else
		{
			LavaDamageTimerDel.BindUFunction(this, TEXT("CalculateDamageTime"), OtherActor);
			GetWorldTimerManager().SetTimer(LavaDamageTimer, LavaDamageTimerDel, CallRate, true);
		}
	}
}

void ALavaFloor::CalculateDamageTime(AActor* OtherActor)
{
	GiveDamage();
	UE_LOG(LogTemp, Warning, TEXT("Player took damage from lava."));
}

void ALavaFloor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		GetWorldTimerManager().PauseTimer(LavaDamageTimer);
	}
}
