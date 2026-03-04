#pragma once

#include "CoreMinimal.h"
#include "Actors/Traps/BaseTrap.h"
#include "GravityTrap.generated.h"

UCLASS()
class UE_TD6_RESEAU_API AGravityTrap : public ABaseTrap
{
	GENERATED_BODY()

	AGravityTrap();
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> SecondaryStaticMesh;

	
	virtual void BeginPlay() override;

	virtual void OnRep_IsActivated() override;

	FVector InitPos;

	FTimerHandle SecondaryMeshTimer;

	void ShowSecondaryMesh();
};
