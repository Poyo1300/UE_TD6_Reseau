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

	UPROPERTY(ReplicatedUsing = OnTeamChanged, BlueprintReadWrite)
	int TeamID = 1;

public:

	UFUNCTION(BlueprintImplementableEvent)
	void OnTeamChanged();
};
