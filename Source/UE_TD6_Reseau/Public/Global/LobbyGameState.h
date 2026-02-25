#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LobbyGameState.generated.h"

UCLASS()
class UE_TD6_RESEAU_API ALobbyGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent)
	void AddPlayer(AController* Controller, int team);
};
