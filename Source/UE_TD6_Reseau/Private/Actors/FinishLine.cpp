// Fill out your copyright notice in the Description page of Project Settings.
#include "Actors/FinishLine.h"
#include "Components/BoxComponent.h"
#include "Global/CustomGameMode.h"
#include "Player/CustomCharacter.h"

// Sets default values
AFinishLine::AFinishLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMesh->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");
	BoxComponent->SetupAttachment(RootComponent);

	if (BoxComponent)
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFinishLine::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinishLine::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TObjectPtr<ACustomCharacter> Char = Cast<ACustomCharacter>(OtherActor);
	if (Char)
	{
		TObjectPtr<ACustomGameMode> GM = GetWorld()->GetAuthGameMode<ACustomGameMode>();
		if (GM)
		{
			GM->SetSpectatorMode(Char->GetController());
		}
	}
	
}

