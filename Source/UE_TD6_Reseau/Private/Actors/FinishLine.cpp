#include "Actors/FinishLine.h"
#include "Components/BoxComponent.h"
#include "Global/CustomGameMode.h"
#include "Player/CustomCharacter.h"

AFinishLine::AFinishLine()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMesh->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");
	BoxComponent->SetupAttachment(RootComponent);

	if (BoxComponent)
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFinishLine::OnOverlapBegin);
}

void AFinishLine::BeginPlay()
{
	Super::BeginPlay();
	
}

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