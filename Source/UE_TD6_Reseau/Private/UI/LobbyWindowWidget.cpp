#include "UI/LobbyWindowWidget.h"
#include "Global/OnlineSessionSubsystem.h"

#include "Components/Button.h"

void ULobbyWindowWidget::NativeConstruct()
{
	OnlineSessionSubsystem = GetGameInstance()->GetSubsystem<UOnlineSessionSubsystem>();

	if (Button_Refresh)
		Button_Refresh->OnClicked.AddDynamic(this, &ULobbyWindowWidget::OnRefreshButtonClicked);
	if (Button_Create)
		Button_Create->OnClicked.AddDynamic(this, &ULobbyWindowWidget::OnCreateButtonClicked);
	if (Button_Join)
		Button_Join->OnClicked.AddDynamic(this, &ULobbyWindowWidget::OnJoinButtonClicked);
		
}

void ULobbyWindowWidget::OnRefreshButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Refresh");
}

void ULobbyWindowWidget::OnCreateButtonClicked()
{
	OnlineSessionSubsystem->CreateSession("Session", -1, false);
}

void ULobbyWindowWidget::OnJoinButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Join");
}
