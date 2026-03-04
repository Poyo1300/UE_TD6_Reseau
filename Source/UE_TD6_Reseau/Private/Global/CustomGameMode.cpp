#include "Global/CustomGameMode.h"

void ACustomGameMode::SetSpectatorMode(AController* Controller)
{
	if (!Controller) return;

	TObjectPtr<APawn> Pawn = Controller->GetPawn();
	if (Pawn)
		Pawn->Destroy();

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "SpecatorMode");

	RestartPlayer(Controller); //respawn de base pour eviter le crash
}
