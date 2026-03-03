#include "Global/CustomGameMode.h"

void ACustomGameMode::HandlePlayerDeath(AController* Controller)
{
	if (!Controller) return;

	TObjectPtr<APawn> Pawn = Controller->GetPawn();
	if (Pawn)
		Pawn->Destroy();

	//Controller->UnPossess();
	Controller->ChangeState(NAME_Spectating);
	
	RestartPlayer(Controller);

}
