// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/SettlerInformations/Entries/ResidenceEntryWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/UserWidgets/SettlerInformations/SettlerInformationWidget.h"
#include "NorthernCamp/UserWidgets/Universal/Popups/ConfirmationPopupWidget.h"

bool UResidenceEntryWidget::Initialize()
{
	bool Success = Super::Initialize();

	bIsSelected = false;

	B_ThisSelected->OnClicked.AddDynamic(this,  &UResidenceEntryWidget::Selected);

	return true;
	
}


void UResidenceEntryWidget::Selected()
{
	for (FConstPlayerControllerIterator iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
	{
		PlayerController = Cast<ANorthernCampPlayerController>(*iter);
	}
	if(PlayerController == nullptr)
	{
		return;
	}


	
	AcceptPopupWidget = WidgetTree->ConstructWidget<UUserWidget>(PlayerController->UIController->ConfirmationPopupWidget);


	if(AcceptPopupWidget != nullptr) 
	{
		AcceptPopupWidget->AddToViewport();

		UConfirmationPopupWidget* AcceptPopup = Cast<UConfirmationPopupWidget>(AcceptPopupWidget);
		if(AcceptPopup)
		{
			AcceptPopup->B_Accept->OnClicked.AddDynamic(this, &UResidenceEntryWidget::Accepted);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("could not cast to accept popup!"));
		}


	}
}

void UResidenceEntryWidget::Accepted()
{
	if(!Building || !PlayerController){return;}

	USleepingSpot* SleepingSpot = Building->AddInhabitant(PlayerController->SelectedSettler);

	if(SleepingSpot == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not add inhabitant using the select building button!"));
	}
	PlayerController->SelectedSettler->CurrentResidence = Building;
	
	//Update ui
	USettlerInformationWidget* InfoUserWidget = Cast<USettlerInformationWidget>(PlayerController->UIController->MainUI);
	InfoUserWidget->RefreshSettlerInfo();

	
	PlayerController->UIController->RemovePopup(EPopup::SelectResidence);
	AcceptPopupWidget->RemoveFromViewport();
}

