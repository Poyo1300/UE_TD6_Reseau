#include "Player/CustomCharacter.h"
#include "Actors/TrapButton.h"

ACustomCharacter::ACustomCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ACustomCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACustomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomCharacter::Interact()
{
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FVector ViewLocation;
	FRotator ViewRotation;
	GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);

	FVector End = ViewLocation + ViewRotation.Vector() * InteractRange;

	if (!GetWorld()->LineTraceSingleByChannel(Hit, ViewLocation, End, ECC_Visibility, Params))
		return;

	if (TObjectPtr<ATrapButton> TrapButton = Cast<ATrapButton>(Hit.GetActor()))
	{
		TrapButton->Press();
	}
}
