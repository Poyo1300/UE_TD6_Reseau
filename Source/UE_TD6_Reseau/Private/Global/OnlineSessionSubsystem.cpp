#include "Global/OnlineSessionSubsystem.h"
#include "Global/MenuGameMode.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineBeaconHost.h"
#include "beacons/LobbyBeaconHostObject.h"
#include "beacons/LobbyBeaconClient.h"

void UOnlineSessionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Session = Online::GetSessionInterface(GetWorld());
}

void UOnlineSessionSubsystem::CreateSession(const FString& SessionName, int32 NumPublicConnections, bool bIsLANMatch)
{
	if (!Session.IsValid()) return;

	LastSessionSettings = MakeShareable(new FOnlineSessionSettings());
	
	LastSessionSettings->NumPublicConnections = NumPublicConnections;
	LastSessionSettings->bIsLANMatch = bIsLANMatch;
	LastSessionSettings->bShouldAdvertise = true;
	LastSessionSettings->bAllowJoinInProgress = true;
	LastSessionSettings->bUsesPresence = true;
	LastSessionSettings->bAllowJoinViaPresence = true;
	LastSessionSettings->bIsDedicated = false;

	LastSessionSettings->Set("SETTING_SESSIONNAME", SessionName, EOnlineDataAdvertisementType::ViaOnlineService);
	LastSessionSettings->Set("SETTING_SESSIONMAXPLAYERS", NumPublicConnections, EOnlineDataAdvertisementType::ViaOnlineService);

	CreateHandle = Session->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(this, &UOnlineSessionSubsystem::OnCreateSessionCompleted));

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	if (!Session->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings))
	{
		Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateHandle);
		return;
	}
}

void UOnlineSessionSubsystem::FindSessions(int32 MaxSearchResults, bool bIsLANQuery)
{
	if (!Session.IsValid()) return;

	FindHandle = Session->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsCompleteDelegate::CreateUObject(this, &UOnlineSessionSubsystem::OnFindSessionsCompleted));

	LastSessionSearch = MakeShareable(new FOnlineSessionSearch());
	LastSessionSearch->bIsLanQuery = bIsLANQuery;
	LastSessionSearch->MaxSearchResults = MaxSearchResults;

	LastSessionSearch->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	if (!Session->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), LastSessionSearch.ToSharedRef()))
	{
		Session->ClearOnFindSessionsCompleteDelegate_Handle(FindHandle);
		return;
	}
}

void UOnlineSessionSubsystem::CustomJoinSessions(const FSessionInfo& SessionInfo)
{
	const FOnlineSessionSearchResult& TempResult = SearchResults[SessionInfo.SessionSearchResultIndex];

	FString ConnectString;
	FName name = NAME_GameSession;

	if (Session->GetResolvedConnectString(TempResult, NAME_GameSession, ConnectString))
	{
		ALobbyBeaconClient* BeaconClient = GetWorld()->SpawnActor<ALobbyBeaconClient>();

		FURL Destination = FURL(nullptr, *ConnectString, ETravelType::TRAVEL_Absolute);
		Destination.Port = 7787;

		UE_LOG(LogTemp, Warning, TEXT("Attempting to connect to server with URL: %s"), *Destination.ToString());

		BeaconClient->ConnectToServer(Destination);

		BeaconClient->OnRequestValidate.BindLambda([this, TempResult](bool bIsValid)
			{
				if (bIsValid)
				{
					//JoinGameSession(SessionInfo);
				}
				else
				{
					OnSessionJoinCompleted.Broadcast(false);
				}
			});
	}
}

void UOnlineSessionSubsystem::JoinGameSession(const FSessionInfo& SessionInfo)
{
	if (!Session.IsValid()) return;

	const FOnlineSessionSearchResult& TempResult = SearchResults[SessionInfo.SessionSearchResultIndex];

	if (SessionInfo.CurrentPlayers == SessionInfo.MaxPlayers)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Session full");

		return;
	}

	JoinHandle = Session->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionCompleteDelegate::CreateUObject(this, &UOnlineSessionSubsystem::OnJoinSessionCompleted));

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	if (!Session->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, TempResult))
	{
		Session->ClearOnJoinSessionCompleteDelegate_Handle(JoinHandle);
		return;
	}
}

void UOnlineSessionSubsystem::DestroySession()
{
	if (!Session.IsValid()) return;

	DestroyHandle = Session->AddOnDestroySessionCompleteDelegate_Handle(FOnDestroySessionCompleteDelegate::CreateUObject(this, &UOnlineSessionSubsystem::OnDestroySessionCompleted));

	if (!Session->DestroySession(NAME_GameSession))
	{
		Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroyHandle);
		return;
	}
}

void UOnlineSessionSubsystem::CreateHostBeacon(int32 ListenPort, bool bOverridePort)
{
	AOnlineBeaconHost* BeaconHost = GetWorld()->SpawnActor<AOnlineBeaconHost>();

	/*if (bOverridePort)
	{
		BeaconHost->ListenPort = ListenPort;
	}*/

	if (BeaconHost->InitHost())
	{
		BeaconHost->PauseBeaconRequests(false);

		if (ALobbyBeaconHostObject* HostObject = GetWorld()->SpawnActor<ALobbyBeaconHostObject>())
		{
			HostObject->ReservedSlots++;
			HostObject->MaxSlots = MaxPlayers;

			BeaconHost->RegisterHost(HostObject);
			UE_LOG(LogTemp, Warning, TEXT("Host beacon created, port listening : %d"), BeaconHost->ListenPort);
		}
	}
}

template<typename ValueType>
inline void UOnlineSessionSubsystem::UpdateCustomSetting(const FName& SettingName, const ValueType& SettingValue, EOnlineDataAdvertisementType::Type AdvertisementType)
{
	if (!Session)
	{
		return;
	}

	if (!LastSessionSettings)
	{
		return;
	}

	TSharedPtr<FOnlineSessionSettings> UpdatedSettings = MakeShareable(new FOnlineSessionSettings(*LastSessionSettings));

	UpdatedSettings->Set(SettingName, SettingValue, AdvertisementType);

	UpdateHandle = Session->AddOnUpdateSessionCompleteDelegate_Handle(
		FOnUpdateSessionCompleteDelegate::CreateUObject(this,
			&UOnlineSessionSubsystem::OnSettingsUpdatedCompleted));

	if (!Session->UpdateSession(NAME_GameSession, *UpdatedSettings))
	{
		Session->ClearOnUpdateSessionCompleteDelegate_Handle(UpdateHandle);
		return;
	}

	LastSessionSettings = UpdatedSettings;
}

void UOnlineSessionSubsystem::OnCreateSessionCompleted(FName SessionName, bool bSuccessful)
{
	if(Session)
		Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateHandle);

	if (!bSuccessful) return;

	GetWorld()->ServerTravel("/Game/Maps/LobbyLevel?listen");
}

void UOnlineSessionSubsystem::OnFindSessionsCompleted(bool bSuccessful)
{
	if (Session) 
		Session->ClearOnFindSessionsCompleteDelegate_Handle(FindHandle);

	SearchResults = LastSessionSearch->SearchResults;
	GEngine->AddOnScreenDebugMessage(-1, 1, (SearchResults.Num() > 0 ? FColor::Green : FColor::Red), FString::Printf(TEXT("%d sessions found"), SearchResults.Num()));

	if (SearchResults.IsEmpty())
	{
		OnFindSessionsCompletedEvent.Broadcast(TArray<FSessionInfo>(), bSuccessful);
		return;
	}

	TArray<FSessionInfo> SessionInfos;

	for (int i = 0; i < SearchResults.Num(); i++)
	{
		FOnlineSessionSearchResult Result = SearchResults[i];

		FSessionInfo SessionInfo;
		FString SessionName;
		Result.Session.SessionSettings.Get("SETTING_SESSIONNAME", SessionName);
		SessionInfo.SessionName = SessionName;
		SessionInfo.MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;
		SessionInfo.CurrentPlayers = Result.Session.SessionSettings.NumPublicConnections - Result.Session.NumOpenPublicConnections;
		SessionInfo.Ping = Result.PingInMs;
		SessionInfo.SessionSearchResultIndex = i;

		SessionInfos.Add(SessionInfo);
	}

	SearchResultsInfos = SessionInfos;
	OnFindSessionsCompletedEvent.Broadcast(SessionInfos, bSuccessful);
}

void UOnlineSessionSubsystem::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	FString ConnectString;

	if (!Session) return;

	Session->ClearOnJoinSessionCompleteDelegate_Handle(JoinHandle);

	if (Result != EOnJoinSessionCompleteResult::Success ||!Session->GetResolvedConnectString(NAME_GameSession, ConnectString)) return;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	PlayerController->ClientTravel(ConnectString, ETravelType::TRAVEL_Absolute);
}

void UOnlineSessionSubsystem::OnDestroySessionCompleted(FName SessionName, bool bSuccessful)
{
	if(Session)
		Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroyHandle);
}

void UOnlineSessionSubsystem::OnSettingsUpdatedCompleted(FName SessionName, bool bSuccessful)
{
}
