// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/Popups/SelectResidencePopup.h"

#include "EngineUtils.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"
#include "NorthernCamp/UserWidgets/SmallElements/SelectBuildingButtons.h"


bool USelectResidencePopup::Initialize()
{
	bool Success = Super::Initialize();




	return true;
}

void USelectResidencePopup::NativeConstruct()
{
	Super::NativeConstruct();


	for (FConstPlayerControllerIterator iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
	{
		PlayerController = Cast<ANorthernCampPlayerController>(*iter);
	}
	if(PlayerController == nullptr)
	{
		return;
	}

	B_QuitPopup->OnClicked.AddDynamic(this, &USelectResidencePopup::Exit);


	UGP_BuildingIcons->ClearChildren();


	//Get all buildings that have a residence
	for (TActorIterator<ABuildingBaseActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{ 
		ABuildingBaseActor* Building = Cast<ABuildingBaseActor>(*ActorItr);

		int32 RowNumber = 0;
		int32 ColumnNumber = 0;

		if(ActorItr->GetFreeSleepingSpots().Num() >= 1)
		{
			
			if(ColumnNumber >= 3)
			{
				ColumnNumber = 0;
				RowNumber++;
			}
	
			WidgetINeed = WidgetTree->ConstructWidget<UUserWidget>(PlayerController->UIController->SelectBuildingIcons);

			
			if(UUniformGridSlot* SlotToUse = UGP_BuildingIcons->AddChildToUniformGrid(WidgetINeed))
			{

				USelectBuildingButtons* BuildingButton = Cast<USelectBuildingButtons>(WidgetINeed);
				BuildingButton->IMG_BuildingIcon->SetBrush(ActorItr->BuildingIcon);
				BuildingButton->TX_BuildingName->SetText(ActorItr->BuildingName);
				BuildingButton->Building = *ActorItr;
				SlotToUse->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
				SlotToUse->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
				SlotToUse->SetRow(RowNumber);
				SlotToUse->SetColumn(ColumnNumber);
			}
			
			ColumnNumber++;
		}
	}
}

void USelectResidencePopup::Exit()
{
	PlayerController->UIController->RemovePopup(EPopup::SelectResidence);
}


