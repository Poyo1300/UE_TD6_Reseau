#pragma once

#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OnlineSessionSubsystem.generated.h"

UCLASS()
class UE_TD6_RESEAU_API UOnlineSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UFUNCTION(BlueprintCallable, Category="Session")
	void CreateSession(FName SessionName, int32 NumPublicConnections, bool bIsLANMatch);

private:
	IOnlineSessionPtr Session;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;

	FDelegateHandle CreateHandle;

	void OnCreateSessionComplete(FName SessionName, bool bSuccessful);
};
