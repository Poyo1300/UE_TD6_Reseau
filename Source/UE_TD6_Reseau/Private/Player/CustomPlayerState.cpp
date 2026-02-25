#include "Player/CustomPlayerState.h"

void ACustomPlayerState::BeginPlay()
{
	Super::BeginPlay();

	bReplicates = true;
}

void ACustomPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACustomPlayerState, TeamID);
}
