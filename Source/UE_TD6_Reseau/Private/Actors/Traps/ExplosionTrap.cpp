// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Traps/ExplosionTrap.h"

void AExplosionTrap::ActivateTrap()
{
	Super::ActivateTrap();
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Explosion trap activated");
}
