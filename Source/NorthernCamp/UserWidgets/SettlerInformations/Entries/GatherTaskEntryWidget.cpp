// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/SettlerInformations/Entries/GatherTaskEntryWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/UserWidgets/SettlerInformations/SettlerInformationWidget.h"
#include "NorthernCamp/UserWidgets/Universal/Popups/ConfirmationPopupWidget.h"


bool UGatherTaskEntryWidget::Initialize()
{
	bool Success = Super::Initialize();



	B_ThisSelected->OnClicked.AddDynamic(this,  &UGatherTaskEntryWidget::Selected);

	return true;
	
}




void UGatherTaskEntryWidget::Selected()
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
			AcceptPopup->B_Accept->OnClicked.AddDynamic(this, &UGatherTaskEntryWidget::Accepted);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("could not cast to accept popup!"));
		}
	}
}

void UGatherTaskEntryWidget::Accepted()
{
	if(!PlayerController || !PlayerController->SelectedSettler){return;}

	ACharacterSettler* Settler = PlayerController->SelectedSettler;
	//Set settler task
	Settler->CurrentWork.WorkType = EWorkType::Building;
	//Check if settler has work spot in building
	Settler->ResetCurrentWork();
	Settler->CurrentWork.WorkType = EWorkType::Gather;
	Settler->CurrentWork.ResourceToGather = ResourceToGather;
	//Update ui
	USettlerInformationWidget* InfoUserWidget = Cast<USettlerInformationWidget>(PlayerController->UIController->MainUI);
	InfoUserWidget->RefreshSettlerInfo();

	PlayerController->UIController->RemovePopup(EPopup::SelectResidence);
	AcceptPopupWidget->RemoveFromViewport();
}




