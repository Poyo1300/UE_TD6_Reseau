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

	CreateHandle = Session->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(this, &UOnlineSessionSubsystem::OnCreateSessionComplete));

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	if (!Session->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), SessionName, *LastSessionSettings))
	{
		Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateHandle);
		return;
	}
}

void UOnlineSessionSubsystem::OnCreateSessionComplete(FName SessionName, bool bSuccessful)
{
	if(Session)
		Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateHandle);

	if (!bSuccessful) return;

	GetWorld()->ServerTravel("/Game/Maps/LobbyLevel?listen");
}
