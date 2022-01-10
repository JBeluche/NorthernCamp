// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/SmallElements/SelectBuildingButtons.h"

#include "Blueprint/WidgetTree.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/UserWidgets/SettlerInfoUserWidget.h"
#include "NorthernCamp/UserWidgets/Popups/AcceptPopup.h"

bool USelectBuildingButtons::Initialize()
{
	bool Success = Super::Initialize();

	bIsSelected = false;

	B_ThisSelected->OnClicked.AddDynamic(this,  &USelectBuildingButtons::Selected);

	return true;
	
}


void USelectBuildingButtons::Selected()
{
	for (FConstPlayerControllerIterator iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
	{
		PlayerController = Cast<ANorthernCampPlayerController>(*iter);
	}
	if(PlayerController == nullptr)
	{
		return;
	}


	
	AcceptPopupWidget = WidgetTree->ConstructWidget<UUserWidget>(PlayerController->UIController->AcceptPopup);


	if(AcceptPopupWidget != nullptr) 
	{
		AcceptPopupWidget->AddToViewport();

		UAcceptPopup* AcceptPopup = Cast<UAcceptPopup>(AcceptPopupWidget);
		if(AcceptPopup)
		{
			AcceptPopup->B_Accept->OnClicked.AddDynamic(this, &USelectBuildingButtons::Accepted);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("could not cast to accept popup!"));
		}


	}
}

void USelectBuildingButtons::Accepted()
{
	if(!Building || !PlayerController){return;}

	USleepingSpot* SleepingSpot = Building->AddInhabitant(PlayerController->SelectedSettler);

	if(SleepingSpot == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not add inhabitant using the select building button!"));
	}
	//Update ui
	USettlerInfoUserWidget* InfoUserWidget = Cast<USettlerInfoUserWidget>(PlayerController->UIController->MainUI);
	InfoUserWidget->RefreshSettlerInfo();

	
	PlayerController->SelectedSettler->CurrentResidence = Building;
	PlayerController->UIController->RemovePopup(EPopup::SelectResidence);
	AcceptPopupWidget->RemoveFromViewport();
}




