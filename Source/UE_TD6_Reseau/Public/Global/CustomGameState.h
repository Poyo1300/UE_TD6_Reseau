#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CustomGameState.generated.h"

UCLASS()
class UE_TD6_RESEAU_API ACustomGameState : public AGameState
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintCallable)
	void EndGame();

public:

	UPROPERTY(BlueprintReadWrite)
	int GameTime = 60;
};
