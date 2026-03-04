// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Traps/BaseTrap.h"
#include "ExplosionTrap.generated.h"

class USphereComponent;
class UAudioComponent;
/**
 * 
 */
UCLASS()
class UE_TD6_RESEAU_API AExplosionTrap : public ABaseTrap
{
	GENERATED_BODY()
protected:

	virtual void BeginPlay() override;

	AExplosionTrap();

	UPROPERTY(EditAnywhere)
	float ExplosionRadius = 500.f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> ExplosionRange;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> Sound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> AudioComponent;
public:

	virtual void OnRep_IsActivated() override;
};
