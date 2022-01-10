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
		
		Settler = Cast<ACharacterSettler>(PlayerController->SelectedSettler);


		if (!ensure(B_BackButton != nullptr)) return false;
		B_BackButton->OnReleased.AddDynamic(this, &USettlerInfoUserWidget::ExitInfoPanel);

		if (!ensure(B_TimeManager != nullptr)) return false;
		B_TimeManager->OnReleased.AddDynamic(this, &USettlerInfoUserWidget::OpenScheduleSettler);

		B_SetWork->OnReleased.AddDynamic(this, &USettlerInfoUserWidget::OpenSelectWorkPopup);
		B_SetResidence->OnReleased.AddDynamic(this, &USettlerInfoUserWidget::OpenSelectResidencePopup);
		
		if(Settler)
		{

			//TODO Naming not perfect!
			RefreshSettlerInfo();
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
/*
void USettlerInfoUserWidget::OpenScheduleSettler()
{
	PlayerController->OpenPopup(UUserWidget*);
}*/

void USettlerInfoUserWidget::ExitInfoPanel()
{
	PlayerController->UIController->UpdateUI(ECurrentUI::LooseCamera);
}

void USettlerInfoUserWidget::OpenScheduleSettler()
{
	PlayerController->UIController->DisplayPopup(EPopup::SettlerSchedule);
}
void USettlerInfoUserWidget::OpenSelectResidencePopup()
{
	PlayerController->UIController->DisplayPopup(EPopup::SelectResidence);
}

void USettlerInfoUserWidget::OpenSelectWorkPopup()
{
	PlayerController->UIController->DisplayPopup(EPopup::SelectWork);
}


void USettlerInfoUserWidget::RefreshSettlerInfo()
{
	//TODO Remove the use of resource to display the icon. You should have global stuff to display globally used icons like an "x".
	T_Work->SetText(FText::FromString(TEXT("No work")));
	FResourceTypeInfo ResourceInfoNone =  PlayerController->ResourceController->ResourcesInfoMap[EResourceType::None];
	IMG_Work->SetBrush(ResourceInfoNone.ResouceIcon);
	T_Residence->SetText(FText::FromString(TEXT("No home")));
	IMG_Residence->SetBrush(ResourceInfoNone.ResouceIcon);
	
	if(Settler->CurrentWork.WorkType == EWorkType::Gather)
	{
		FText WorkType = FText::FromString(*UEnum::GetDisplayValueAsText(Settler->CurrentWork.WorkType).ToString());

		EResourceType ResourceType = Settler->CurrentWork.ResourceToGather;
		FResourceTypeInfo ResourceInfo =  PlayerController->ResourceController->ResourcesInfoMap[ResourceType];
		FText AditionalText = FText::FromString(" /n");

		FText TextToSet = FText::Format(WorkType,AditionalText, ResourceInfo.DisplayName);

		T_Work->SetText(TextToSet);
		IMG_Work->SetBrush(ResourceInfo.ResouceIcon);
	}
	else if(Settler->CurrentWork.WorkType == EWorkType::Building)
	{
		FText BuildingName = Settler->CurrentWork.WorkBuilding->BuildingName;
				
		FText AditionalText = FText::FromString("Working at: /n");
				
		FText TextToSet = FText::Format(AditionalText, BuildingName);
		T_Work->SetText(TextToSet);
		IMG_Work->SetBrush(Settler->CurrentWork.WorkBuilding->BuildingIcon);
	}

	UE_LOG(LogTemp, Error, TEXT("When through here"));

	//Residence
	if(Settler->CurrentResidence != nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Not a nullptr"));

		T_Residence->SetText(Settler->CurrentResidence->BuildingName);
		IMG_Residence->SetBrush(Settler->CurrentResidence->BuildingIcon);
	}
}





