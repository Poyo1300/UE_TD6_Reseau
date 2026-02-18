#include "Beacons/LobbyBeaconHostObject.h"
#include "beacons/LobbyBeaconClient.h"

ALobbyBeaconHostObject::ALobbyBeaconHostObject(const FObjectInitializer& Initializer)
{
	ClientBeaconActorClass = ALobbyBeaconClient::StaticClass();

	BeaconTypeName = ClientBeaconActorClass->GetName();
}

void ALobbyBeaconHostObject::OnClientConnected(AOnlineBeaconClient* NewClientActor, UNetConnection* ClientConnection)
{
	Super::OnClientConnected(NewClientActor, ClientConnection);

	if (NewClientActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("New client connected: %s"), *NewClientActor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("A client connected but no actor was created."));
	}
}

AOnlineBeaconClient* ALobbyBeaconHostObject::SpawnBeaconActor(UNetConnection* ClientConnection)
{
	return Super::SpawnBeaconActor(ClientConnection);
}
