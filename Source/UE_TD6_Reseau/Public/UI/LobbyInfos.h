#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyInfos.generated.h"

class UButton;
class UTextBlock;
class UOnlineSessionSubsystem;
UCLASS()
class UE_TD6_RESEAU_API ULobbyInfos : public UUserWidget
{
	GENERATED_BODY()
	
private:
	virtual void NativeConstruct() override;

	TObjectPtr<UOnlineSessionSubsystem> OnlineSessionSubsystem;
protected:

	UFUNCTION()
	void OnSelectButtonClicked();

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Select;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Name;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentPlayers;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxPlayers;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Ping;

	UPROPERTY()
	bool bIsSelected = false;
};
