// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Traps/GravityTrap.h"

void AGravityTrap::OnRep_IsActivated()
{
	Super::OnRep_IsActivated();

	StaticMesh->SetEnableGravity(true);
}

void AGravityTrap::ActivateTrap()
{
	Super::ActivateTrap();
}
