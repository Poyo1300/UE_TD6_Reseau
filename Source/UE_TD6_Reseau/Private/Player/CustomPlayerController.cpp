#include "Player/CustomPlayerController.h"
#include "Player/CustomCharacter.h"
#include "Global/CustomGameInstance.h"

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

	if (EndGameWidgetClass)
	{
		EndGameWidget = CreateWidget<UEndGameWidget>(GetWorld(), EndGameWidgetClass);
		if (EndGameWidget)
		{
			EndGameWidget->AddToViewport();
			EndGameWidget->SetVisibility(ESlateVisibility::Hidden);
			bIsMenuOpen = false;
		}
	}
}

void ACustomPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	t += DeltaTime;
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

void ACustomPlayerController::Interact(const FInputActionValue& Value)
{
	if (TObjectPtr<ACustomCharacter> CustomChara = Cast<ACustomCharacter>(GetPawn()))
	{
		CustomChara->Interact();
	}
}

void ACustomPlayerController::OpenMenu(const FInputActionValue& Value)
{
	if (t > 2.f)
	{
		t = 0.f;
		if (bIsMenuOpen)
		{
			if (EndGameWidget)
			{
				EndGameWidget->SetVisibility(ESlateVisibility::Hidden);

				TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController();
				if (PlayerController)
				{
					PlayerController->bShowMouseCursor = false;
					PlayerController->SetInputMode(FInputModeGameOnly());
				}

			}
		}
		else
		{
			if (EndGameWidget)
			{
				EndGameWidget->SetVisibility(ESlateVisibility::Visible);

				TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController();
				if (PlayerController)
				{
					PlayerController->bShowMouseCursor = true;
					PlayerController->SetInputMode(FInputModeUIOnly());
				}

			}
		}
	}
	bIsMenuOpen = !bIsMenuOpen;
}
