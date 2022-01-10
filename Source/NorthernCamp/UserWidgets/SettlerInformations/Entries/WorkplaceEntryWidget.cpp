// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/SettlerInformations/Entries/WorkplaceEntryWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"
#include "NorthernCamp/UserWidgets/SettlerInformations/SettlerInformationWidget.h"
#include "NorthernCamp/UserWidgets/Universal/Popups/ConfirmationPopupWidget.h"

bool UWorkplaceEntryWidget::Initialize()
{
	bool Success = Super::Initialize();

	B_ThisSelected->OnClicked.AddDynamic(this,  &UWorkplaceEntryWidget::Selected);
	
	return true;
}


void UWorkplaceEntryWidget::Selected()
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
			AcceptPopup->B_Accept->OnClicked.AddDynamic(this, &UWorkplaceEntryWidget::Accepted);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("could not cast to accept popup!"));
		}


	}
}

void UWorkplaceEntryWidget::Accepted()
{
	if(!Building || !PlayerController){return;}

	UWorkingSpot* WorkingSpot = Building->AddWorker(PlayerController->SelectedSettler);

	if(WorkingSpot == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not add inhabitant using the select building button!"));
	}
	//Update ui
	USettlerInformationWidget* InfoUserWidget = Cast<USettlerInformationWidget>(PlayerController->UIController->MainUI);
	InfoUserWidget->RefreshSettlerInfo();
	
	PlayerController->SelectedSettler->CurrentWork.WorkBuilding = Building;
	PlayerController->SelectedSettler->CurrentWork.WorkType = EWorkType::Building;
	
	PlayerController->UIController->RemovePopup(EPopup::SelectWork);
	AcceptPopupWidget->RemoveFromViewport();
}

