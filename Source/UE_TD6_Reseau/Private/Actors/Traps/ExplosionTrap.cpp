// Fill out your copyright notice in the Description page of Project Settings.
#include "Actors/Traps/ExplosionTrap.h"
#include "Player/CustomCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"

void AExplosionTrap::BeginPlay()
{
	if (Sound)
		AudioComponent->SetSound(Sound);
}

AExplosionTrap::AExplosionTrap()
{
	ExplosionRange = CreateDefaultSubobject<USphereComponent>("Range");
	ExplosionRange->SetSphereRadius(500.f);
	ExplosionRange->SetupAttachment(RootComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio Component");
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bAutoActivate = false;
}

void AExplosionTrap::OnRep_IsActivated()
{
	Super::OnRep_IsActivated();
	FVector Location = GetActorLocation();
	TArray<AActor*> ActorsInRange;

	GetOverlappingActors(ActorsInRange, ACustomCharacter::StaticClass());
	
	for (AActor* Actor : ActorsInRange)
	{
		ACustomCharacter* Character = Cast<ACustomCharacter>(Actor);
		Character->Kill();
	}

	if (Sound)
		AudioComponent->Play();

	Destroy();
}