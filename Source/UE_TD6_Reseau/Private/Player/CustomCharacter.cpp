#include "Player/CustomCharacter.h"
#include "Actors/TrapButton.h"
#include "Global/CustomGameMode.h"
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

	if (GetActorLocation().Z < -500.f)
		Kill();
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

void ACustomCharacter::Kill()
{

	TObjectPtr<ACustomGameMode> GM = GetWorld()->GetAuthGameMode<ACustomGameMode>();
	if (GM)
		GM->SetSpectatorMode(GetController());
	//Destroy();
}
