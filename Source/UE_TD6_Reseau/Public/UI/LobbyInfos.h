#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"
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

	UPROPERTY(BlueprintReadWrite)
	bool bIsSelected = false;


	TSharedPtr<FOnlineSessionSearchResult> Session;
};
