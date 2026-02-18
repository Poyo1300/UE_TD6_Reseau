#include "Global/LobbyGameMode.h"

void ALobbyGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	GameSession->MaxPlayers = GetGameInstance()->GetSubsystem<UOnlineSessionSubsystem>()->MaxPlayers;

}

void ALobbyGameMode::OnPostLogin(AController* Controller)
{
	Super::OnPostLogin(Controller);

	AddPlayer(Controller);
}

void ALobbyGameMode::Logout(AController* Exiting)
{
}

void ALobbyGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
}

void ALobbyGameMode::DestroyGame()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		if (AMenuController* PC = Cast<AMenuController>(It->Get()))
		{
			PC->DestroySessionOnClient();
		}
	}
}
