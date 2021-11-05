// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/UserWidgets/LooseCameraMainUserWidget.h"

#include "EngineUtils.h"
#include "Components/TextBlock.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "NorthernCamp/Characters/CharacterHero.h"
#include "NorthernCamp/Controllers/DayNightActorController.h"
#include "Engine/World.h"

bool ULooseCameraMainUserWidget::Initialize()
{
	bool Success = Super::Initialize();
	if(!Success) return false;

	if (!ensure(CampView != nullptr)) return false;
	CampView->OnClicked.AddDynamic(this, &ULooseCameraMainUserWidget::SwitchToCamp);
	
	if (!ensure(ButtonWill != nullptr)) return false;
	ButtonWill->OnClicked.AddDynamic(this, &ULooseCameraMainUserWidget::SwitchToWill);

	if (!ensure(ButtonTrader != nullptr)) return false;
	ButtonTrader->OnClicked.AddDynamic(this, &ULooseCameraMainUserWidget::SwitchToTrader);

		
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

			GetWorld()->GetTimerManager().SetTimer(UpdateClockTimerHandle, this, &ULooseCameraMainUserWidget::SetClock, 0.5f, true);
    	}

	return true;
}
void ULooseCameraMainUserWidget::SetClock()
{
	
	FNumberFormattingOptions NumberFormat;					

	NumberFormat.MaximumIntegralDigits = 2;
	NumberFormat.MinimumFractionalDigits = -1;

	FString Hour = FText::AsNumber(DayNightController->CurrentTimeHours, &NumberFormat).ToString();
	FString Minutes = FText::AsNumber(DayNightController->CurrentTimeMinutes, &NumberFormat).ToString();

	FString Time = Hour + ':' + Minutes;

	TB_Clock->SetText(FText::FromString(Time));
}
void ULooseCameraMainUserWidget::SwitchToCamp()
{
	PlayerController->SwitchPawn(ECurrentPawn::Camp);
}


void ULooseCameraMainUserWidget::SwitchToWill()
{
	PlayerController->SetSelectedHero(EHero::Will);

}
void ULooseCameraMainUserWidget::SwitchToTrader()
{
	PlayerController->SetSelectedHero(EHero::Trader);
}
void ULooseCameraMainUserWidget::SwitchToHunter()
{
	
}
void ULooseCameraMainUserWidget::SwitchToSeaclan()
{
	
}
void ULooseCameraMainUserWidget::SwitchToMinedweler()
{
	
}
void ULooseCameraMainUserWidget::SwitchToDruida()
{
	
}
void ULooseCameraMainUserWidget::SwitchToAlchemist()
{
	
}
void ULooseCameraMainUserWidget::SwitchToOccultist()
{
	
}