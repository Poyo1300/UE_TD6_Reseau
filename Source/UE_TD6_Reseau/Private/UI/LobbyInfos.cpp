#include "UI/LobbyInfos.h"
#include "Components/Button.h"
#include "UI/LobbyWindowWidget.h"

void ULobbyInfos::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Select)
		Button_Select->OnClicked.AddDynamic(this, &ULobbyInfos::OnSelectButtonClicked);
}

void ULobbyInfos::OnSelectButtonClicked()
{
	
}
