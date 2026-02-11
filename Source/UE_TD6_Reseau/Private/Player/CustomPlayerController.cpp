#include "Player/CustomPlayerController.h"

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!MappingContextGame)
	{
		return;
	}

	if (GetLocalPlayer())
	{
		if (TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(MappingContextGame, 0);
		}
	}

	MyPlayer = Cast<ACustomCharacter>(GetPawn());
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		for (FInputActionSetup i : IA_Setup)
		{
			EnhancedInputComponent->BindAction(i.Action, i.Event, this, i.ActionName.GetMemberName());
		}
	}
}

void ACustomPlayerController::Move(const FInputActionValue& Value)
{
	FVector MovementVector = Value.Get<FVector>();

	FRotator CameraRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);

	FVector RotatedVector = CameraRotation.RotateVector(MovementVector);

	GetPawn()->AddMovementInput(RotatedVector);
}

void ACustomPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddYawInput(LookAxisVector.X * CameraSensitivity * GetWorld()->GetDeltaSeconds());
	AddPitchInput(LookAxisVector.Y * CameraSensitivity * GetWorld()->GetDeltaSeconds());
}

void ACustomPlayerController::Jump(const FInputActionValue& Value)
{
	if (MyPlayer)
	{
		MyPlayer->Jump();
	}
}
