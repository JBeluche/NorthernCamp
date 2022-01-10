// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/Popups/SelectWorkPopup.h"

#include "EngineUtils.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/UserWidgets/SmallElements/SelectWorkBuilding.h"
#include "NorthernCamp/UserWidgets/SmallElements/SelectWorkButton.h"


bool USelectWorkPopup::Initialize()
{
	bool Success = Super::Initialize();
	return true;
}

void USelectWorkPopup::NativeConstruct()
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

	B_QuitPopup->OnClicked.AddDynamic(this, &USelectWorkPopup::Exit);

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

void USelectWorkPopup::AddBuildingsWithWorkButtons()
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
			UE_LOG(LogTemp, Error, TEXT("is not the smae building"));
			if(ActorItr->GetFreeWorkingSpot().Num() >= 1)
			{
				UE_LOG(LogTemp, Error, TEXT("Has free spots!"));

				
				if(ColumnNumber >= 3)
				{
					ColumnNumber = 0;
					RowNumber++;
				}
		
				WidgetINeed = WidgetTree->ConstructWidget<UUserWidget>(PlayerController->UIController->ButtonWorkBuilding);

				
				if(UUniformGridSlot* SlotToUse = UGP_WorkBuilding->AddChildToUniformGrid(WidgetINeed))
				{

					USelectWorkBuilding* BuildingButton = Cast<USelectWorkBuilding>(WidgetINeed);
					if(BuildingButton == nullptr){return;}
					BuildingButton->IMG_Icon->SetBrush(ActorItr->BuildingIcon);
					BuildingButton->TX_Name->SetText(ActorItr->BuildingName);
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
}

void USelectWorkPopup::AddGatherResourceButtons()
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

				WidgetINeed = WidgetTree->ConstructWidget<UUserWidget>(PlayerController->UIController->ButtonGatherResource);
			
				if(UUniformGridSlot* SlotToUse = UGP_GatherResource->AddChildToUniformGrid(WidgetINeed))
				{

					USelectWorkButton* ButtonGatherResource = Cast<USelectWorkButton>(WidgetINeed);
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

void USelectWorkPopup::Exit()
{
	PlayerController->UIController->RemovePopup(EPopup::SelectWork);
}

