// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Traps/BaseTrap.h"
#include "ExplosionTrap.generated.h"

/**
 * 
 */
UCLASS()
class UE_TD6_RESEAU_API AExplosionTrap : public ABaseTrap
{
	GENERATED_BODY()

public:

	virtual void ActivateTrap() override;
};
