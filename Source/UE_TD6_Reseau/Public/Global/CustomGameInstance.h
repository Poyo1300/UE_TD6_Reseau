#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

UCLASS()
class UE_TD6_RESEAU_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite)
	TArray<APlayerController*> Team1Players;
	UPROPERTY(BlueprintReadWrite)
	TArray<APlayerController*> Team2Players;
};
