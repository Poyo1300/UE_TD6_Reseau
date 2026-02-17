#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "UI/LobbyWindowWidget.h"
#include "MenuGameMode.generated.h"

UCLASS()
class UE_TD6_RESEAU_API AMenuGameMode : public AGameMode
{
	GENERATED_BODY()
	
protected:

	AMenuGameMode();
	virtual void BeginPlay() override;

public: 

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ULobbyWindowWidget> LobbyWindowWidget;

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveOldLobby();

	UFUNCTION(BlueprintImplementableEvent)
	void AddLobbyInfo(const FString& SessionName, int CurrentPlayers, int MaxPlayers, float Ping);
};
