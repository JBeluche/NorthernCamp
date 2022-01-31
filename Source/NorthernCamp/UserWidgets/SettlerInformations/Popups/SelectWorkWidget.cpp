// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/SettlerInformations/Popups/SelectWorkWidget.h"


#include "EngineUtils.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/UserWidgets/SettlerInformations/SettlerInformationWidget.h"
#include "NorthernCamp/UserWidgets/SettlerInformations/Entries/GatherTaskEntryWidget.h"
#include "NorthernCamp/UserWidgets/SettlerInformations/Entries/WorkplaceEntryWidget.h"
#include "NorthernCamp/UserWidgets/Universal/Popups/ConfirmationPopupWidget.h"


bool USelectWorkWidget::Initialize()
{
	bool Success = Super::Initialize();
	return true;
}

void USelectWorkWidget::NativeConstruct()
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

	//Dynamic functions
	B_Clear->OnClicked.AddDynamic(this, &USelectWorkWidget::OpenAcceptPopup);
	B_QuitPopup->OnClicked.AddDynamic(this, &USelectWorkWidget::Exit);
	
	//Check if you need to display de clear button
	if(PlayerController->SelectedSettler->CurrentWork.WorkType != EWorkType::None)
	{
		B_Clear->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		B_Clear->SetVisibility(ESlateVisibility::Hidden);
	}
	

	UGP_GatherResource->ClearChildren();

	UGP_WorkBuilding->ClearChildren();

	//Check if there is something to be gathered.
	for (TActorIterator<AResourceController> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ResourceController = *ActorItr;
		
	}

	for (TActorIterator<AResourceController> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ResourceController = *ActorItr;
		
	}

	
	if(ResourceController)
	{
		if(PlayerController == nullptr){return;}
		AddGatherResourceButtons();
		AddBuildingsWithWorkButtons();
	}
}

void USelectWorkWidget::AddBuildingsWithWorkButtons()
{
	int32 RowNumber = 0;
	int32 ColumnNumber = 0;

	for (TActorIterator<ABuildingBaseActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{ 
		ABuildingBaseActor* Building = Cast<ABuildingBaseActor>(*ActorItr);

		if(PlayerController->SelectedSettler->CurrentWork.WorkBuilding)
		{
			UE_LOG(LogTemp, Error, TEXT("Settler building: %s, Found building: %s"), *PlayerController->SelectedSettler->CurrentWork.WorkBuilding->GetName(), *Building->GetName());
		}
		
		if(PlayerController->SelectedSettler->CurrentWork.WorkBuilding != Building)
		{
			if(ActorItr->GetFreeWorkingSpot().Num() >= 1)
			{
				if(ColumnNumber >= 3)
				{
					ColumnNumber = 0;
					RowNumber++;
				}
		
				EntryWidget = WidgetTree->ConstructWidget<UUserWidget>(PlayerController->UIController->WorkplaceEntryWidget);

				
				if(UUniformGridSlot* SlotToUse = UGP_WorkBuilding->AddChildToUniformGrid(EntryWidget))
				{

					UWorkplaceEntryWidget* WorkbuildingEntry = Cast<UWorkplaceEntryWidget>(EntryWidget);
					if(WorkbuildingEntry == nullptr){return;}
					WorkbuildingEntry->IMG_Icon->SetBrush(ActorItr->BuildingIcon);
					WorkbuildingEntry->TX_Name->SetText(ActorItr->BuildingName);
					WorkbuildingEntry->Building = *ActorItr;
					SlotToUse->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
					SlotToUse->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
					SlotToUse->SetRow(RowNumber);
					SlotToUse->SetColumn(ColumnNumber);
				}
				
				ColumnNumber++;
			}
		}

	}
}

void USelectWorkWidget::AddGatherResourceButtons()
{


	int32 RowNumber = 0;
	int32 ColumnNumber = 0;
	
	for(EResourceType ResourceType : ResourceController->GatherableResources)
	{
		if(PlayerController->SelectedSettler->CurrentWork.ResourceToGather != ResourceType)
		{
			bool bHasResourceInfo = ResourceController->ResourcesInfoMap.Contains(ResourceType);
			if(bHasResourceInfo)
			{

				if(ColumnNumber >= 3)
				{
					ColumnNumber = 0;
					RowNumber++;
				}

				EntryWidget = WidgetTree->ConstructWidget<UUserWidget>(PlayerController->UIController->GatherTaskEntryWidget);
			
				if(UUniformGridSlot* SlotToUse = UGP_GatherResource->AddChildToUniformGrid(EntryWidget))
				{

					UGatherTaskEntryWidget* ButtonGatherResource = Cast<UGatherTaskEntryWidget>(EntryWidget);
					if(ButtonGatherResource == nullptr){return;}
					ButtonGatherResource->IMG_Icon->SetBrush(ResourceController->ResourcesInfoMap[ResourceType].ResouceIcon);
					ButtonGatherResource->TX_Name->SetText(ResourceController->ResourcesInfoMap[ResourceType].DisplayName);
					ButtonGatherResource->ResourceToGather = ResourceType;
					SlotToUse->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
					SlotToUse->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
					SlotToUse->SetRow(RowNumber);
					SlotToUse->SetColumn(ColumnNumber);
				}
			
				ColumnNumber++;
			}
		}
	}
}

void USelectWorkWidget::Exit()
{
	PlayerController->UIController->RemovePopup(EPopup::SelectWork);
}

void USelectWorkWidget::OpenAcceptPopup()
{
	AcceptPopupWidget = WidgetTree->ConstructWidget<UUserWidget>(PlayerController->UIController->ConfirmationPopupWidget);
	
	if(AcceptPopupWidget != nullptr)
	{
		AcceptPopupWidget->AddToViewport();

		UConfirmationPopupWidget* AcceptPopup = Cast<UConfirmationPopupWidget>(AcceptPopupWidget);
		if(AcceptPopup)
		{
			AcceptPopup->B_Accept->OnClicked.AddDynamic(this, &USelectWorkWidget::ClearWork);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("could not cast to accept popup!"));
		}
	}
}

void USelectWorkWidget::ClearWork()
{

	PlayerController->SelectedSettler->ResetCurrentWork();

	//Update ui
	USettlerInformationWidget* InfoUserWidget = Cast<USettlerInformationWidget>(PlayerController->UIController->MainUI);
	InfoUserWidget->RefreshSettlerInfo();
	
	PlayerController->UIController->RemovePopup(EPopup::SelectWork);
	AcceptPopupWidget->RemoveFromViewport();
}
	