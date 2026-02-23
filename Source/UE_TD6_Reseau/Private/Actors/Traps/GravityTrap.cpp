// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Traps/GravityTrap.h"

void AGravityTrap::ActivateTrap()
{
	Super::ActivateTrap();

	StaticMesh->SetEnableGravity(true);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Gravity trap activated");
}
