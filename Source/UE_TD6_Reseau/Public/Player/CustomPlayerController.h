#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "CustomCharacter.h"
#include "CustomPlayerController.generated.h"

class UEndGameWidget;

USTRUCT(BlueprintType)
struct FInputActionSetup
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	TObjectPtr<UInputAction> Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	ETriggerEvent Event = ETriggerEvent::Triggered;

	UPROPERTY(EditAnywhere, meta = (FunctionReference, PrototypeFunction = "/Script/UE_TD6_Reseau.CustomPlayerController.Prototype_InputAction"))
	FMemberReference ActionName;
};

UCLASS()
class UE_TD6_RESEAU_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	bool bIsMenuOpen;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void OnDestroy();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	TObjectPtr<class UInputMappingContext> MappingContextGame = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	TArray<FInputActionSetup> IA_Setup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraSensitivity = 30.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UEndGameWidget> EndGameWidgetClass = nullptr;

	UPROPERTY()
	TObjectPtr<UEndGameWidget> EndGameWidget = nullptr;
private:
	float t;

	UPROPERTY(Transient)
	TObjectPtr<ACustomCharacter> MyPlayer = nullptr;


#if WITH_EDITOR
	UFUNCTION(BlueprintInternalUseOnly)
	void Prototype_InputAction(const FInputActionValue& Value) {};
#endif

	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Jump(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Interact(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void OpenMenu(const FInputActionValue& Value);
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdatePlayerLives(int Value);
};
