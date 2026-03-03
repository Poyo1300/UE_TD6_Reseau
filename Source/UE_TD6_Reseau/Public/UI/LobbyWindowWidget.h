#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWindowWidget.generated.h"

class UButton;
class USlider;
class UOnlineSessionSubsystem;
UCLASS()
class UE_TD6_RESEAU_API ULobbyWindowWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

	TObjectPtr<UOnlineSessionSubsystem> OnlineSessionSubsystem;
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Button_Refresh;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Button_Create;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Button_Join;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> Slider_Players;

	UFUNCTION()
	void OnRefreshButtonClicked();

	UFUNCTION()
	void OnCreateButtonClicked();
	
	UFUNCTION()
	void OnJoinButtonClicked();
};
