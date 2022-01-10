// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/SettlerInformations/Popups/ScheduleSettingsWidget.h"



#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "NorthernCamp/NorthernCampPlayerController.h"

bool UScheduleSettingsWidget::Initialize()
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
	}
	if(Settler)
	{
		//Set the slider to correct 
		HandleSteps(ESlider::Sleep, Settler->SleepHoursAmount);
		HandleSteps(ESlider::Fun, Settler->FunHoursAmount );
		HandleSteps(ESlider::Work, Settler->WorkHoursAmount);

		Slider_Work->OnValueChanged.AddDynamic(this, &UScheduleSettingsWidget::HandleSliderChangeWork);
		Slider_Sleep->OnValueChanged.AddDynamic(this, &UScheduleSettingsWidget::HandleSliderChangedSleep);
		Slider_Fun->OnValueChanged.AddDynamic(this, &UScheduleSettingsWidget::HandleSliderChangedFun);

		B_Accept->OnClicked.AddDynamic(this, &UScheduleSettingsWidget::SaveSchedule);
		B_Cancel->OnClicked.AddDynamic(this, &UScheduleSettingsWidget::ClosePopup);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Miraculously the popupsettlerschedule could not cast to settler"));
	}

		
	
	return Success;
}

void UScheduleSettingsWidget::SaveSchedule()
{
	Settler->WorkHoursAmount = Slider_Work->GetValue();
	Settler->SleepHoursAmount = Slider_Sleep->GetValue();
	Settler->FunHoursAmount = Slider_Fun->GetValue();

	ClosePopup();	
}

void UScheduleSettingsWidget::ClosePopup()
{
	PlayerController->UIController->RemovePopup(EPopup::SettlerSchedule);
}

void UScheduleSettingsWidget::HandleSliderChangedFun(float InValue)
{
	HandleSteps(ESlider::Fun, InValue);
	
}
void UScheduleSettingsWidget::HandleSliderChangeWork(float InValue)
{
	HandleSteps(ESlider::Work, InValue);

}
void UScheduleSettingsWidget::HandleSliderChangedSleep(float InValue)
{
	HandleSteps(ESlider::Sleep, InValue);

}

void UScheduleSettingsWidget::HandleSteps(ESlider Slider,float InValue)
{
	float Rounded = roundf(InValue);
	FString CurrentHoursToDisplay = FString::SanitizeFloat(Rounded);
	
	if(Slider == ESlider::Fun)
	{
		float OverValue = (Rounded + Slider_Sleep->GetValue() + Slider_Work->GetValue()) - 24.0f;
		if(OverValue > 0.0f)
		{
			for(int i = 0; i < OverValue; i++)
			{
				if(Slider_Work->GetValue() > Slider_Sleep->GetValue())
				{
					Slider_Work->SetValue(Slider_Work->GetValue() - 1.0f);
					TB_WorkHours->SetText(FText::FromString(FString::SanitizeFloat(Slider_Work->GetValue())));
				}
				else
				{
					Slider_Sleep->SetValue(Slider_Sleep->GetValue() - 1.0f);
					TB_SleepHours->SetText(FText::FromString(FString::SanitizeFloat(Slider_Sleep->GetValue())));

				}
			}
		}
		Slider_Fun->SetValue(Rounded);
		TB_FunHours->SetText(FText::FromString(CurrentHoursToDisplay));
	
	}
	else if(Slider == ESlider::Sleep)
	{

		float OverValue = (Rounded + Slider_Fun->GetValue() + Slider_Work->GetValue()) - 24.0f;

		if(OverValue)
		{
			for(int i = 0; i < OverValue; i++)
			{
				if(Slider_Fun->GetValue() > 0.0f)
				{
					Slider_Fun->SetValue(Slider_Fun->GetValue() - 1.0f);
					TB_FunHours->SetText(FText::FromString(FString::SanitizeFloat(Slider_Fun->GetValue())));

				}
				else
				{
					Slider_Work->SetValue(Slider_Work->GetValue() - 1.0f);
					TB_WorkHours->SetText(FText::FromString(FString::SanitizeFloat(Slider_Work->GetValue())));

				}
			}
		}
		
		Slider_Sleep->SetValue(Rounded);
		TB_SleepHours->SetText(FText::FromString(CurrentHoursToDisplay));

	}
	
	else if(Slider == ESlider::Work)
	{

		float OverValue = (Rounded + Slider_Fun->GetValue() + Slider_Sleep->GetValue()) - 24.0f;

		if(OverValue)
		{
			for(int i = 0; i < OverValue; i++)
			{
				if(Slider_Fun->GetValue() > 0.0f)
				{
					Slider_Fun->SetValue(Slider_Fun->GetValue() - 1.0f);
					TB_FunHours->SetText(FText::FromString(FString::SanitizeFloat(Slider_Fun->GetValue())));

				}
				else
				{
					Slider_Sleep->SetValue(Slider_Sleep->GetValue() - 1.0f);
					TB_SleepHours->SetText(FText::FromString(FString::SanitizeFloat(Slider_Sleep->GetValue())));

				}
			}
			
		}
		Slider_Work->SetValue(Rounded);
		TB_WorkHours->SetText(FText::FromString(CurrentHoursToDisplay));
	}

}