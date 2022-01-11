// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/SettlerInformations/Popups/SelectResidenceWidget.h"

#include "EngineUtils.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"
#include "NorthernCamp/UserWidgets/SettlerInformations/SettlerInformationWidget.h"
#include "NorthernCamp/UserWidgets/SettlerInformations/Entries/ResidenceEntryWidget.h"
#include "NorthernCamp/UserWidgets/Universal/Popups/ConfirmationPopupWidget.h"


bool USelectResidenceWidget::Initialize()
{
	bool Success = Super::Initialize();

	return true;
}

void USelectResidenceWidget::NativeConstruct()
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

	B_Clear->OnClicked.AddDynamic(this, &USelectResidenceWidget::OpenAcceptPopup);
	//Check if you need to display de clear button
	if(PlayerController->SelectedSettler->CurrentResidence != nullptr)
	{
		B_Clear->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		B_Clear->SetVisibility(ESlateVisibility::Hidden);
	}

		
	B_QuitPopup->OnClicked.AddDynamic(this, &USelectResidenceWidget::Exit);


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
	
			WidgetINeed = WidgetTree->ConstructWidget<UUserWidget>(PlayerController->UIController->ResidenceEntryWidget);

			
			if(UUniformGridSlot* SlotToUse = UGP_BuildingIcons->AddChildToUniformGrid(WidgetINeed))
			{

				UResidenceEntryWidget* BuildingButton = Cast<UResidenceEntryWidget>(WidgetINeed);
				// te fuck ? BuildingButton->IMG_BuildingIcon->SetBrush(ActorItr->BuildingIcon);
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

void USelectResidenceWidget::Exit()
{
	PlayerController->UIController->RemovePopup(EPopup::SelectResidence);
}

void USelectResidenceWidget::OpenAcceptPopup()
{
	AcceptPopupWidget = WidgetTree->ConstructWidget<UUserWidget>(PlayerController->UIController->ConfirmationPopupWidget);
	
	if(AcceptPopupWidget != nullptr)
	{
		AcceptPopupWidget->AddToViewport();

		UConfirmationPopupWidget* AcceptPopup = Cast<UConfirmationPopupWidget>(AcceptPopupWidget);
		if(AcceptPopup)
		{
			AcceptPopup->B_Accept->OnClicked.AddDynamic(this, &USelectResidenceWidget::ClearResidence);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("could not cast to accept popup!"));
		}
	}
}


void USelectResidenceWidget::ClearResidence()
{
	PlayerController->SelectedSettler->ResetCurrentResidence();

	//Update ui
	USettlerInformationWidget* InfoUserWidget = Cast<USettlerInformationWidget>(PlayerController->UIController->MainUI);
	InfoUserWidget->RefreshSettlerInfo();
	
	PlayerController->UIController->RemovePopup(EPopup::SelectWork);
	AcceptPopupWidget->RemoveFromViewport();
}
	
