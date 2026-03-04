#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "CustomCharacter.generated.h"

UCLASS()
class UE_TD6_RESEAU_API ACustomCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	ACustomCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere)
	float InteractRange = 100.f;

	UPROPERTY()
	bool bIsDead = false;
	UPROPERTY()
	bool bCanTakeDamage = true;

	FTimerHandle DamageCooldown;

public:

	UPROPERTY(BlueprintReadWrite)
	int Lives = 10;

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void Kill();

	UFUNCTION(Server, Reliable)
	void Respawn();

	UFUNCTION()
	void CanTakeDamage();
};
