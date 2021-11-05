// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/UserWidgets/SettlerInfoUserWidget.h"

#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/Characters/CharacterSettler.h"
#include "Kismet/GameplayStatics.h"
#include "NorthernCamp/CharacterComponents/VitalsComponent.h"


bool USettlerInfoUserWidget::Initialize()
{
	bool Success = Super::Initialize();

	for (FConstPlayerControllerIterator iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
	{
		APlayerController* PlayerControllerIterating = Cast<APlayerController>(*iter);

		PlayerController = Cast<ANorthernCampPlayerController>(PlayerControllerIterating);

	}
	

	if(PlayerController)
	{
		if (!ensure(B_BackButton != nullptr)) return false;
		B_BackButton->OnClicked.AddDynamic(this, &USettlerInfoUserWidget::ExitInfoPanel);
		
		Settler = Cast<ACharacterSettler>(PlayerController->SelectedSettler);

		if(Settler)
		{
			
			UpdateInfoSettler();
			GetWorld()->GetTimerManager().SetTimer(UpdateInfoSettlerTimerHandle, this, &USettlerInfoUserWidget::UpdateInfoSettler, 5.0f, true);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("The cast to settler has failed in widget"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The cast to controller has failed in widget"));
	}
	return true;

}

void USettlerInfoUserWidget::UpdateInfoSettler()
{

	TB_SettlersName->SetText(Settler->Name);

	//Vitals settler
	CharacterVitalsComponent = Cast<UVitalsComponent>(Settler->GetCharacterVitalsComponent());

	if(CharacterVitalsComponent)
	{

		float CurrentWaterInPercentage = (1.0f * CharacterVitalsComponent->CurrentWaterMeter) / 100.0f;
		float CurrentFoodInPercentage = (1.0f * CharacterVitalsComponent->CurrentFoodMeter) / 100.0f;
		float CurrentSleepInPercentage = (1.0f * CharacterVitalsComponent->CurrentSleepMeter) / 100.0f;
		float CurrentFunFireInPercentage = (1.0f * CharacterVitalsComponent->CurrentFunFireMeter) / 100.0f;

		PB_HealthMeter->SetPercent(CurrentWaterInPercentage);
	
		PB_WaterMeter->SetPercent(CurrentWaterInPercentage);

		PB_FoodMeter->SetPercent(CurrentFoodInPercentage);

		PB_SleepMeter->SetPercent(CurrentSleepInPercentage);
	
		PB_FunFireMeter->SetPercent(CurrentFunFireInPercentage);
	}

}

void USettlerInfoUserWidget::ExitInfoPanel()
{
	if(PlayerController)
	{

		PlayerController->UpdateUI(ECurrentUI::LooseCamera);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Something went wrong in the Settlers info user widget. Could not find playercontroller"))
	}
}






