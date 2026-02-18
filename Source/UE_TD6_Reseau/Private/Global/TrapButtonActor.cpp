// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/TrapButtonActor.h"

// Sets default values
ATrapButtonActor::ATrapButtonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrapButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapButtonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrapButtonActor::Press()
{
}

