#include "Global/CustomGameMode.h"
#include "GameFramework/SpectatorPawn.h"

void ACustomGameMode::SetSpectatorMode(AController* Controller)
{
	if (!Controller) return;
	TObjectPtr<APawn> Pawn = Controller->GetPawn();

	ASpectatorPawn* SpectatorPawn;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Controller;
	
	SpectatorPawn = GetWorld()->SpawnActor<ASpectatorPawn>(ActorToSpawn, Pawn->GetActorLocation(), Pawn->GetActorRotation(), SpawnParams);

	Controller->UnPossess();
	if (Pawn)
		Pawn->Destroy();

	Controller->Possess(SpectatorPawn);
}

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
