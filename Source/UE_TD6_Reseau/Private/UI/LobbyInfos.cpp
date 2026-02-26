#include "UI/LobbyInfos.h"
#include "Components/Button.h"
#include "UI/LobbyWindowWidget.h"

void ULobbyInfos::NativeConstruct()
{
	Super::NativeConstruct();

	OnlineSessionSubsystem = GetGameInstance()->GetSubsystem<UOnlineSessionSubsystem>();

	if (Button_Select)
		Button_Select->OnClicked.AddDynamic(this, &ULobbyInfos::OnSelectButtonClicked);
}

void ULobbyInfos::OnSelectButtonClicked()
{
	if (bIsSelected)
	{
		OnlineSessionSubsystem->SelectedSession = OnlineSessionSubsystem->SearchResults[SessionInfos.SessionSearchResultIndex];
		OnlineSessionSubsystem->SelectedSessionInfos = OnlineSessionSubsystem->SearchResultsInfos[SessionInfos.SessionSearchResultIndex];
	}
	else
	{
		OnlineSessionSubsystem->SelectedSession = FOnlineSessionSearchResult();
		OnlineSessionSubsystem->SelectedSessionInfos = FSessionInfo();
	}
}
