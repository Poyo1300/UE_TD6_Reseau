#include "Global/OnlineSessionSubsystem.h"

#include "Online/OnlineSessionNames.h"
#include "OnlineSubsystemUtils.h"

void UOnlineSessionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Session = Online::GetSessionInterface(GetWorld());
}

void UOnlineSessionSubsystem::CreateSession(FName SessionName, int32 NumPublicConnections, bool bIsLANMatch)
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

	CreateHandle = Session->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(this, &UOnlineSessionSubsystem::OnCreateSessionCompleted));

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	if (!Session->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), SessionName, *LastSessionSettings))
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
}
