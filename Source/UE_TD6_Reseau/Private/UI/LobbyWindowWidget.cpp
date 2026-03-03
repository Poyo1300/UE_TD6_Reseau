#include "UI/LobbyWindowWidget.h"
#include "Global/OnlineSessionSubsystem.h"
#include "Global/MenuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "Components/Button.h"

void ULobbyWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnlineSessionSubsystem = GetGameInstance()->GetSubsystem<UOnlineSessionSubsystem>();

	if (Button_Refresh)
		Button_Refresh->OnClicked.AddDynamic(this, &ULobbyWindowWidget::OnRefreshButtonClicked);
	if (Button_Create)
		Button_Create->OnClicked.AddDynamic(this, &ULobbyWindowWidget::OnCreateButtonClicked);
	if (Button_Join)
		Button_Join->OnClicked.AddDynamic(this, &ULobbyWindowWidget::OnJoinButtonClicked);
		
	if (AMenuGameMode* GameMode = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->LobbyWindowWidget = this;
	}
}

void ULobbyWindowWidget::OnRefreshButtonClicked()
{
	OnlineSessionSubsystem->FindSessions(20, false);
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Refresh");
}

void ULobbyWindowWidget::OnCreateButtonClicked()
{
	int index = GetWorld()->GetFirstLocalPlayerFromController()->GetLocalPlayerIndex();
	APlayerState* PS = UGameplayStatics::GetPlayerState(GetWorld(), index);
	OnlineSessionSubsystem->CreateSession(PS->GetPlayerName() + FString(TEXT("'s room")), 10, false);
}

void ULobbyWindowWidget::OnJoinButtonClicked()
{
	const FOnlineSessionSearchResult& TempResult = OnlineSessionSubsystem->SelectedSession;

	if (TempResult.IsValid())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Join");
		OnlineSessionSubsystem->JoinGameSession(OnlineSessionSubsystem->SelectedSessionInfos);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "No session selected");
	}
}
