#include "Actors/TrapButton.h"
#include "Actors/Traps/BaseTrap.h"

ATrapButton::ATrapButton()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static mesh component");
	StaticMesh->SetupAttachment(RootComponent);

	bReplicates = true;
}

void ATrapButton::BeginPlay()
{
	Super::BeginPlay();
}

void ATrapButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrapButton::Press()
{
	if (LinkedTrap)
	{
		LinkedTrap->ActivateTrap();
	}
}
