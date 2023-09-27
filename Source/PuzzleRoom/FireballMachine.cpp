// Fill out your copyright notice in the Description page of Project Settings.

#include "FireballMachine.h"
#include "Fireball.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"


//TODO: Player takes damage through logs.
//TODO: Maybe make a fireball vfx.
//https://docs.unrealengine.com/4.26/en-US/ProgrammingAndScripting/ProgrammingWithCPP/CPPTutorials/FirstPersonShooter/3/

// Sets default values
AFireballMachine::AFireballMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}
	if (!MachineMesh)
	{
		MachineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MachineMesh"));
		MachineMesh->SetupAttachment(RootComponent);
	}

}

// Called when the game starts or when spawned
void AFireballMachine::BeginPlay()
{
	Super::BeginPlay();
	
	InitialCooldown = 0.f;
}

// Called every frame
void AFireballMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Fire(DeltaTime);

}

void AFireballMachine::Fire(float DeltaTime)
{
	if (InitialCooldown > 0)
	{
		InitialCooldown -= DeltaTime;
	}
	else
	{
		ThrowFireball();
		InitialCooldown = IgnitionPeriod;
	}
}

void AFireballMachine::ThrowFireball()
{
	if (FireballClass)
	{
		FVector BarrelLocation = GetActorLocation() + BarrelOffset;
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			AFireball* Fireball = World->SpawnActor<AFireball>(FireballClass, BarrelLocation, GetActorRotation(), SpawnParams);
			if (Fireball)
			{
				Fireball->OnFireballSpawned.AddUniqueDynamic(this, &AFireballMachine::OnFireballSpawned);
				FVector IgnitionDirection = GetActorRotation().Vector();
				Fireball->ThrowToDirection(IgnitionDirection);
			}
		}
	}
}

void AFireballMachine::OnFireballSpawned(UNiagaraSystem* TrailFX, USphereComponent* AttachComp)
{
	UNiagaraFunctionLibrary::SpawnSystemAttached(TrailFX, AttachComp, NAME_None, AttachComp->GetComponentLocation(), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);
}