#include "Player/CustomCharacter.h"
#include "Actors/TrapButton.h"
#include "Player/CustomPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/CustomPlayerState.h"
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
	
	if (IsLocallyControlled() && bCanTakeDamage)
	{
		FVector Location = GetActorLocation();
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, FString::Printf(TEXT("%f"), Location.Z));
		if (Location.Z < -500.f && !bIsDead)
			Kill();
	}
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
	Lives--;
	bCanTakeDamage = false;
	
	TObjectPtr<ACustomPlayerController> PC = Cast<ACustomPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->UpdatePlayerLives(Lives);

	if (Lives <= 0)
	{
		TObjectPtr<ACustomGameMode> GM = GetWorld()->GetAuthGameMode<ACustomGameMode>();
		if (GM)
			GM->HandlePlayerDeath(GetController());
		bIsDead = true;
		return;
		//Destroy();
	}
	
	Respawn();

	GetWorldTimerManager().SetTimer(DamageCooldown, this, &ACustomCharacter::CanTakeDamage, 1.f, false);
}

void ACustomCharacter::Respawn_Implementation()
{
	TObjectPtr<ACustomPlayerState> PS = Cast<ACustomPlayerState>(GetPlayerState());

	if (PS->TeamID == 1)
		SetActorLocation(FVector(-700.f, 880.f, 92.f));
	else if (PS->TeamID == 2)
		SetActorLocation(FVector(-700.f, 90.f, 92.f));
}

void ACustomCharacter::CanTakeDamage()
{
	bCanTakeDamage = true;
	GetWorldTimerManager().ClearTimer(DamageCooldown);
}