// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/SettlerInformations/SettlerInformationWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/CharacterComponents/VitalsComponent.h"

bool USettlerInformationWidget::Initialize()
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
		B_BackButton->OnReleased.AddDynamic(this, &USettlerInformationWidget::ExitInfoPanel);

		if (!ensure(B_TimeManager != nullptr)) return false;
		B_TimeManager->OnReleased.AddDynamic(this, &USettlerInformationWidget::OpenScheduleSettler);

		B_SetWork->OnReleased.AddDynamic(this, &USettlerInformationWidget::OpenSelectWorkPopup);
		B_SetResidence->OnReleased.AddDynamic(this, &USettlerInformationWidget::OpenSelectResidencePopup);
		
		if(Settler)
		{

			//TODO Naming not perfect!
			RefreshSettlerInfo();
			UpdateInfoSettler();
			GetWorld()->GetTimerManager().SetTimer(UpdateInfoSettlerTimerHandle, this, &USettlerInformationWidget::UpdateInfoSettler, 1.0f, true);
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

void USettlerInformationWidget::UpdateInfoSettler()
{

	TB_SettlersName->SetText(Settler->Name);

	//Vitals settler
	CharacterVitalsComponent = Cast<UVitalsComponent>(Settler->GetCharacterVitalsComponent());

	if(CharacterVitalsComponent)
	{

		float CurrentWaterInPercentage = (1.0f * CharacterVitalsComponent->GetVitalLevel(EVital::Water)) / 100.0f;
		
		float CurrentFoodInPercentage = (1.0f * CharacterVitalsComponent->CurrentFoodMeter) / 100.0f;
		float CurrentSleepInPercentage = (1.0f * CharacterVitalsComponent->CurrentSleepMeter) / 100.0f;
		float CurrentFunFireInPercentage = (1.0f * CharacterVitalsComponent->CurrentFunFireMeter) / 100.0f;


		UE_LOG(LogTemp, Error, TEXT("I just updated the info and the water was: %f, while the bar thinks its %f"), CharacterVitalsComponent->GetVitalLevel(EVital::Water), CurrentWaterInPercentage);

		PB_HealthMeter->SetPercent(CurrentWaterInPercentage);
	
		PB_WaterMeter->SetPercent(CurrentWaterInPercentage);

		PB_FoodMeter->SetPercent(CurrentFoodInPercentage);

		PB_SleepMeter->SetPercent(CurrentSleepInPercentage);
	
		PB_FunFireMeter->SetPercent(CurrentFunFireInPercentage);
	}

}
/*
void USettlerInformationWidget::OpenScheduleSettler()
{
	PlayerController->OpenPopup(UUserWidget*);
}*/

void USettlerInformationWidget::ExitInfoPanel()
{
	PlayerController->UIController->UpdateUI(ECurrentUI::LooseCamera);
}

void USettlerInformationWidget::OpenScheduleSettler()
{
	PlayerController->UIController->DisplayPopup(EPopup::SettlerSchedule);
}
void USettlerInformationWidget::OpenSelectResidencePopup()
{
	PlayerController->UIController->DisplayPopup(EPopup::SelectResidence);
}

void USettlerInformationWidget::OpenSelectWorkPopup()
{
	PlayerController->UIController->DisplayPopup(EPopup::SelectWork);
}


void USettlerInformationWidget::RefreshSettlerInfo()
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
				
		FText AditionalText = FText::FromString("Working at:");
				
		FText TextToSet = FText::Format(AditionalText, BuildingName);
		T_Work->SetText(BuildingName);
		IMG_Work->SetBrush(Settler->CurrentWork.WorkBuilding->BuildingIcon);

	}


	//Residence
	if(Settler->CurrentResidence != nullptr)
	{
		T_Residence->SetText(Settler->CurrentResidence->BuildingName);
		IMG_Residence->SetBrush(Settler->CurrentResidence->BuildingIcon);
	}
}

