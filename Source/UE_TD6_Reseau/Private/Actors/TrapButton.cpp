// Fill out your copyright notice in the Description page of Project Settings.
#include "Actors/TrapButton.h"
#include "Actors/Traps/BaseTrap.h"


// Sets default values
ATrapButton::ATrapButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static mesh component");
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATrapButton::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATrapButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrapButton::Press()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Pressed");
	if (LinkedTrap)
		LinkedTrap->ActivateTrap();
}

