#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Global/OnlineSessionSubsystem.h"
#include "EndGameWidget.generated.h"

class UButton;

UCLASS()
class UE_TD6_RESEAU_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	TObjectPtr<UOnlineSessionSubsystem> OnlineSessionSubsystem;

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MenuButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;

	UFUNCTION()
	void OnMenuButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();
};
