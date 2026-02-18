#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameSession.h"
#include "Player/MenuController.h"
#include "Global/OnlineSessionSubsystem.h"
#include "LobbyGameMode.generated.h"

UCLASS()
class UE_TD6_RESEAU_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void OnPostLogin(AController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	UFUNCTION(BlueprintCallable)
	void DestroyGame();
public:

	UFUNCTION(BlueprintImplementableEvent)
	void AddPlayer(AController* Controller);
};
