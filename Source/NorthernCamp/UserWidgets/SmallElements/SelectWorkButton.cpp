// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/SmallElements/SelectWorkButton.h"

#include "Blueprint/WidgetTree.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/UserWidgets/SettlerInfoUserWidget.h"
#include "NorthernCamp/UserWidgets/Popups/AcceptPopup.h"


bool USelectWorkButton::Initialize()
{
	bool Success = Super::Initialize();



	B_ThisSelected->OnClicked.AddDynamic(this,  &USelectWorkButton::Selected);

	return true;
	
}


void USelectWorkButton::Selected()
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
			AcceptPopup->B_Accept->OnClicked.AddDynamic(this, &USelectWorkButton::Accepted);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("could not cast to accept popup!"));
		}


	}
}

void USelectWorkButton::Accepted()
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
	USettlerInfoUserWidget* InfoUserWidget = Cast<USettlerInfoUserWidget>(PlayerController->UIController->MainUI);
	InfoUserWidget->RefreshSettlerInfo();

	PlayerController->UIController->RemovePopup(EPopup::SelectResidence);
	AcceptPopupWidget->RemoveFromViewport();
}




