#include "Actors/Traps/GravityTrap.h"
#include "TimerManager.h"


AGravityTrap::AGravityTrap()
{
	SecondaryStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Secondary Mesh");
	SecondaryStaticMesh->SetupAttachment(RootComponent);
	SecondaryStaticMesh->SetHiddenInGame(true);
	SecondaryStaticMesh->SetCollisionProfileName("OverlappAll");
}

void AGravityTrap::BeginPlay()
{
	Super::BeginPlay();
	InitPos = GetActorLocation();
}

void AGravityTrap::OnRep_IsActivated()
{
	Super::OnRep_IsActivated();
	if (bIsActivated)
	{
		StaticMesh->SetEnableGravity(true);
		GetWorld()->GetTimerManager().SetTimer(SecondaryMeshTimer, this, &AGravityTrap::ShowSecondaryMesh, 5.f, false);
	}
	else
	{
		StaticMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
		StaticMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
		
		StaticMesh->SetEnableGravity(false);
		SetActorLocation(InitPos);
	}
}

void AGravityTrap::ShowSecondaryMesh()
{
	SecondaryStaticMesh->SetHiddenInGame(false);
	SecondaryStaticMesh->SetCollisionProfileName("BlockAll");
}