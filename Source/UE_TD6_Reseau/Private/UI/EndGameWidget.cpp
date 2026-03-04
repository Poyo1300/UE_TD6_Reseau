#include "UI/EndGameWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UEndGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnlineSessionSubsystem = GetGameInstance()->GetSubsystem<UOnlineSessionSubsystem>();

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UEndGameWidget::OnQuitButtonClicked);
	}
	if (MenuButton)
	{
		MenuButton->OnClicked.AddDynamic(this, &UEndGameWidget::OnMenuButtonClicked);
	}
}

void UEndGameWidget::OnMenuButtonClicked()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		OnlineSessionSubsystem->DestroySession();
		UGameplayStatics::OpenLevel(GetWorld(), "MenuLevel");
	}
}

void UEndGameWidget::OnQuitButtonClicked()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->ConsoleCommand("quit");
	}
}