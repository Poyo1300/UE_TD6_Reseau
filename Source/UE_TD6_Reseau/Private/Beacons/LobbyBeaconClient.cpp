#include "Beacons/LobbyBeaconClient.h"
#include "beacons/LobbyBeaconHostObject.h"

ALobbyBeaconClient::ALobbyBeaconClient(const FObjectInitializer& Initializer) : Super(Initializer)
{

}

void ALobbyBeaconClient::OnConnected()
{
	Super::OnConnected();

	UE_LOG(LogTemp, Warning, TEXT("Connected to server!"));

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	Server_RequestReservation(LocalPlayer->GetPreferredUniqueNetId(), "TestSession");
}

void ALobbyBeaconClient::OnFailure()
{
	Super::OnFailure();

	UE_LOG(LogTemp, Error, TEXT("Failed to connect to server."));
}

bool ALobbyBeaconClient::ConnectToServer(FURL& Url)
{
	return InitClient(Url);
}

void ALobbyBeaconClient::Server_RequestReservation_Implementation(const FUniqueNetIdRepl& UserId, const FString& SessionId)
{
	ALobbyBeaconHostObject* Host = Cast<ALobbyBeaconHostObject>(GetBeaconOwner());

	if (!Host)
	{
		Client_ReservationRejected();
		return;
	}

	if (Host->ReservedSlots >= Host->MaxSlots)
	{
		Client_ReservationRejected();
		return;
	}

	Host->ReservedSlots++;
	Client_ReservationAccepted();
}

void ALobbyBeaconClient::Client_ReservationAccepted_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Reservation accepted by server!"));
	OnRequestValidate.Execute(true);
}

void ALobbyBeaconClient::Client_ReservationRejected_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Reservation rejected by server!"));
	OnRequestValidate.Execute(false);
}