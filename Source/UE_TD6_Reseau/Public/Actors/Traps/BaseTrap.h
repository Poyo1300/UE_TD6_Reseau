// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTrap.generated.h"

UCLASS()
class UE_TD6_RESEAU_API ABaseTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseTrap();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(ReplicatedUsing = OnRep_IsActivated)
	bool bIsActivated;

	UFUNCTION()
	virtual void OnRep_IsActivated();

	UPROPERTY(EditAnywhere)
	float RespawnDelay;

	FTimerHandle RespawnTimer;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void ActivateTrap();

	virtual void Respawn();
	//Cooldown
};
