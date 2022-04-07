// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/Controls/LooseCameraControlsWidget.h"

#include "EngineUtils.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/Controllers/DayNightActorController.h"
#include "NorthernCamp/UserWidgets/CampInformation/Entries/ResouceCounterEntryWidget.h"


bool ULooseCameraControlsWidget::Initialize()
{
	bool Success = Super::Initialize();
	if(!Success) return false;

	if (!ensure(CampView != nullptr)) return false;
	CampView->OnClicked.AddDynamic(this, &ULooseCameraControlsWidget::SwitchToCamp);
	
	if (!ensure(ButtonWill != nullptr)) return false;
	ButtonWill->OnClicked.AddDynamic(this, &ULooseCameraControlsWidget::SwitchToWill);

	if (!ensure(ButtonTrader != nullptr)) return false;
	ButtonTrader->OnClicked.AddDynamic(this, &ULooseCameraControlsWidget::SwitchToTrader);

		
	for (FConstPlayerControllerIterator iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
	{
		APlayerController* PlayerControllerIterating = Cast<APlayerController>(*iter);

		PlayerController = Cast<ANorthernCampPlayerController>(PlayerControllerIterating);

	}

	for (TActorIterator<ADayNightActorController> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		DayNightController = *ActorItr;
	}
	
	if(DayNightController)
    	{

			GetWorld()->GetTimerManager().SetTimer(UpdateClockTimerHandle, this, &ULooseCameraControlsWidget::SetClock, 0.5f, true);
    	}

	return true;
}
void ULooseCameraControlsWidget::SetClock()
{
	UpdateResoucesAmountDisplayed();
	FNumberFormattingOptions NumberFormat;					

	NumberFormat.MaximumIntegralDigits = 2;
	NumberFormat.MinimumFractionalDigits = -1;

	FString Hour = FText::AsNumber(DayNightController->CurrentTimeHours, &NumberFormat).ToString();
	FString Minutes = FText::AsNumber(DayNightController->CurrentTimeMinutes, &NumberFormat).ToString();

	FString Time = Hour + ':' + Minutes;

	TB_Clock->SetText(FText::FromString(Time));
}
void ULooseCameraControlsWidget::SwitchToCamp()
{
	PlayerController->SwitchPawn(ECurrentPawn::Camp);
}


void ULooseCameraControlsWidget::SwitchToWill()
{
	PlayerController->SetSelectedHero(EHero::Will);

}
void ULooseCameraControlsWidget::SwitchToTrader()
{
	PlayerController->SetSelectedHero(EHero::Trader);
}
void ULooseCameraControlsWidget::SwitchToHunter()
{
	
}
void ULooseCameraControlsWidget::SwitchToSeaclan()
{
	
}
void ULooseCameraControlsWidget::SwitchToMinedweler()
{
	
}
void ULooseCameraControlsWidget::SwitchToDruida()
{
	
}
void ULooseCameraControlsWidget::SwitchToAlchemist()
{
	
}
void ULooseCameraControlsWidget::SwitchToOccultist()
{
	
}

void ULooseCameraControlsWidget::UpdateResoucesAmountDisplayed()
{


	TMap<EResourceType, int32> TotalResourcesStored = PlayerController->ResourceController->TotalResourcesStored;
	TMap<EResourceType, FResourceTypeInfo> ResourcesInfoMap = PlayerController->ResourceController->ResourcesInfoMap;

	
	int32 RowNumber = 0;
	int32 ColumnNumber = 0;
	
	for (TPair<EResourceType, int32>& Pair : TotalResourcesStored)
	{
			/*if(ColumnNumber >= 3)
			{
				ColumnNumber = 0; 
				RowNumber++;
			}*/
		if(!PlayerController){UE_LOG(LogTemp, Error, TEXT("ULooseCameraControlsWidget: Nullptr PlayerController")); return;}
		if(!PlayerController->UIController->WorkplaceEntryWidget){UE_LOG(LogTemp, Error, TEXT("ULooseCameraControlsWidget: Nullptr PlayerController->UIController->WorkplaceEntryWidget")); return;}
			if(!EntryWidget)
			{
				EntryWidget = WidgetTree->ConstructWidget<UUserWidget>(PlayerController->UIController->ResourceCounterEntryWidget);
			}
			if(!EntryWidget){UE_LOG(LogTemp, Error, TEXT("LooseCameraControlsWidget: Nullptr entrywidget")); return;}
			/*FWidgetTransform Transform;
			Transform.Scale = FVector2D(0.66f, 0.66f);
			EntryWidget->SetRenderTransform(Transform);*/
		
		
			if(UUniformGridSlot* SlotToUse = UGP_ResoucesTotal->AddChildToUniformGrid(EntryWidget))
			{

				UResouceCounterEntryWidget* ResouceCounterEntry = Cast<UResouceCounterEntryWidget>(EntryWidget);
				if(ResouceCounterEntry == nullptr){return;}

				//Display settings
				if(ResourcesInfoMap.Contains(Pair.Key))
				{
					ResouceCounterEntry->IMG_Icon->SetBrush(ResourcesInfoMap[Pair.Key].ResouceIcon);

				}
				ResouceCounterEntry->TX_Amount->SetText(FText::AsNumber(Pair.Value));

				//Alignments
				/*SlotToUse->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
				SlotToUse->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);*/
				
				
				SlotToUse->SetRow(RowNumber);
				SlotToUse->SetColumn(ColumnNumber);
			}
			
			ColumnNumber++;

		ResourceEntryWidget = WidgetTree->ConstructWidget<UUserWidget>(PlayerController->UIController->ResourceCounterEntryWidget);

	}

}