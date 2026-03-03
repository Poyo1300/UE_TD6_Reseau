#pragma once

#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OnlineSessionSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FSessionInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString SessionName = "";
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentPlayers = 0;
	UPROPERTY(BlueprintReadOnly)
	int32 MaxPlayers = 0;
	UPROPERTY(BlueprintReadOnly)
	int32 Ping = 0;

	int32 SessionSearchResultIndex = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFindSessionsCompleted, const TArray<FSessionInfo>&, SessionResult, bool, bSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionJoinCompleted, bool, bSuccessful);

UCLASS()
class UE_TD6_RESEAU_API UOnlineSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UFUNCTION(BlueprintCallable, Category="Session")
	void CreateSession(const FString& SessionName, int32 NumPublicConnections, bool bIsLANMatch);

	UFUNCTION(BlueprintCallable, Category = "Session")
	void FindSessions(int32 MaxSearchResults, bool bIsLANQuery);

	void CustomJoinSessions(const FSessionInfo& SessionInfo);

	void JoinGameSession(const FSessionInfo& SessionInfo);
	
	UFUNCTION(BlueprintCallable, Category = "Session")
	void DestroySession();

	UFUNCTION(BlueprintCallable, Category = "Beacon")
	void CreateHostBeacon(int32 ListenPort, bool bOverridePort);

	template<typename ValueType>
	void UpdateCustomSetting(const FName& SettingName, const ValueType& SettingValue, EOnlineDataAdvertisementType::Type AdvertisementType);

	UPROPERTY(BlueprintAssignable, Category = "Session")
	FOnFindSessionsCompleted OnFindSessionsCompletedEvent;

	UPROPERTY(BlueprintAssignable, Category = "Session")
	FOnSessionJoinCompleted OnSessionJoinCompleted;

	int32 MaxPlayers = 0;
	TArray<FOnlineSessionSearchResult> SearchResults;
	FOnlineSessionSearchResult SelectedSession;
	TArray<FSessionInfo> SearchResultsInfos;
	FSessionInfo SelectedSessionInfos;

private:
	IOnlineSessionPtr Session;

	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

	FDelegateHandle CreateHandle;
	FDelegateHandle FindHandle;
	FDelegateHandle JoinHandle;
	FDelegateHandle DestroyHandle;
	FDelegateHandle UpdateHandle;

	void OnCreateSessionCompleted(FName SessionName, bool bSuccessful);
	void OnFindSessionsCompleted(bool bSuccessful);
	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionCompleted(FName SessionName, bool bSuccessful);
	void OnSettingsUpdatedCompleted(FName SessionName, bool bSuccessful);
};
