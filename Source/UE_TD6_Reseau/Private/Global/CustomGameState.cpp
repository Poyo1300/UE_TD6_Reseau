#include "Global/CustomGameState.h"

void ACustomGameState::EndGame()
{
	if (HasAuthority())
	{
		GameTime = 60;

		GetWorld()->ServerTravel("/Game/Maps/LobbyLevel?listen");
	}
}
