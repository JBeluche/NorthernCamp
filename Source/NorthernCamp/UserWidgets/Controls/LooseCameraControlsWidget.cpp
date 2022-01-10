// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/Controls/LooseCameraControlsWidget.h"

#include "EngineUtils.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/Controllers/DayNightActorController.h"


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