#include "Player/MenuController.h"
#include "Global/OnlineSessionSubsystem.h"

void AMenuController::DestroySessionOnClient_Implementation()
{
	GetGameInstance()->GetSubsystem<UOnlineSessionSubsystem>()->DestroySession();

	ClientTravel("/Game/Maps/MenuLevel", ETravelType::TRAVEL_Absolute);
}