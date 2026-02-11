#include "Player/CustomCharacter.h"

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