#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "CustomPlayerState.generated.h"

UCLASS()
class UE_TD6_RESEAU_API ACustomPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UPROPERTY(BlueprintReadWrite, Replicated)
	int TeamID = 1;
};
