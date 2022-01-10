// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/SmallElements/SelectWorkBuilding.h"

#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"
#include "NorthernCamp/UserWidgets/Popups/AcceptPopup.h"
#include "Blueprint/WidgetTree.h"
#include "NorthernCamp/UserWidgets/SettlerInfoUserWidget.h"


bool USelectWorkBuilding::Initialize()
{
	bool Success = Super::Initialize();


	B_ThisSelected->OnClicked.AddDynamic(this,  &USelectWorkBuilding::Selected);

	
	return true;
	
}


void USelectWorkBuilding::Selected()
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
			AcceptPopup->B_Accept->OnClicked.AddDynamic(this, &USelectWorkBuilding::Accepted);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("could not cast to accept popup!"));
		}


	}
}

void USelectWorkBuilding::Accepted()
{
	if(!Building || !PlayerController){return;}

	UWorkingSpot* WorkingSpot = Building->AddWorker(PlayerController->SelectedSettler);

	if(WorkingSpot == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not add inhabitant using the select building button!"));
	}
	//Update ui
	USettlerInfoUserWidget* InfoUserWidget = Cast<USettlerInfoUserWidget>(PlayerController->UIController->MainUI);
	InfoUserWidget->RefreshSettlerInfo();
	
	PlayerController->SelectedSettler->CurrentWork.WorkBuilding = Building;
	PlayerController->SelectedSettler->CurrentWork.WorkType = EWorkType::Building;
	
	PlayerController->UIController->RemovePopup(EPopup::SelectWork);
	AcceptPopupWidget->RemoveFromViewport();
}

