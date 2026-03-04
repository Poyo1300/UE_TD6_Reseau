// Fill out your copyright notice in the Description page of Project Settings.
#include "Actors/Traps/BaseTrap.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABaseTrap::ABaseTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static mesh component");
	StaticMesh->SetupAttachment(RootComponent);

	bReplicates = true;
	bIsActivated = false;
}

void ABaseTrap::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseTrap, bIsActivated);
}

// Called when the game starts or when spawned
void ABaseTrap::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseTrap::OnRep_IsActivated()
{
	if (bIsActivated)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, FString::Printf(TEXT("Trap activated: %s"), *GetName()));
		GetWorld()->GetTimerManager().SetTimer(RespawnTimer, this, &ABaseTrap::Respawn, RespawnDelay, false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Trap respawn: %s"), *GetName()));
	}
}

// Called every frame
void ABaseTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseTrap::ActivateTrap()
{
	if (HasAuthority() && !bIsActivated)
	{
		bIsActivated = true;
		OnRep_IsActivated();
	}
}

void ABaseTrap::Respawn()
{
	if (HasAuthority())
	{
		bIsActivated = false;
		OnRep_IsActivated();
	}
}

