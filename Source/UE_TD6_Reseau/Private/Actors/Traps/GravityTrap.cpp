// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Traps/GravityTrap.h"

void AGravityTrap::BeginPlay()
{
	Super::BeginPlay();
	InitPos = GetActorLocation();
}

void AGravityTrap::OnRep_IsActivated()
{
	Super::OnRep_IsActivated();
	if (bIsActivated)
		StaticMesh->SetEnableGravity(true);
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, FString::Printf(TEXT("Gravity Trap activated: %s"), *GetName()));
		StaticMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
		StaticMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
		
		StaticMesh->SetEnableGravity(false);
		SetActorLocation(InitPos);
	}
}