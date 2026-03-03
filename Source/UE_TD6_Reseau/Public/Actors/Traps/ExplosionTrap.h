// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Traps/BaseTrap.h"
#include "ExplosionTrap.generated.h"

class USphereComponent;

/**
 * 
 */
UCLASS()
class UE_TD6_RESEAU_API AExplosionTrap : public ABaseTrap
{
	GENERATED_BODY()
protected:
	AExplosionTrap();

	UPROPERTY(EditAnywhere)
	float ExplosionRadius = 500.f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> ExplosionRange;

public:

	virtual void OnRep_IsActivated() override;
};
