// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/Popups/PopupSettlerSchedule.h"

#include <string>

#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "NorthernCamp/NorthernCampPlayerController.h"

bool UPopupSettlerSchedule::Initialize()
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

		Slider_Work->OnValueChanged.AddDynamic(this, &UPopupSettlerSchedule::HandleSliderChangeWork);
		Slider_Sleep->OnValueChanged.AddDynamic(this, &UPopupSettlerSchedule::HandleSliderChangedSleep);
		Slider_Fun->OnValueChanged.AddDynamic(this, &UPopupSettlerSchedule::HandleSliderChangedFun);

		B_Accept->OnClicked.AddDynamic(this, &UPopupSettlerSchedule::SaveSchedule);
		B_Cancel->OnClicked.AddDynamic(this, &UPopupSettlerSchedule::ClosePopup);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Miraculously the popupsettlerschedule could not cast to settler"));
	}

		
	
	return Success;
}

void UPopupSettlerSchedule::SaveSchedule()
{
	Settler->WorkHoursAmount = Slider_Work->GetValue();
	Settler->SleepHoursAmount = Slider_Sleep->GetValue();
	Settler->FunHoursAmount = Slider_Fun->GetValue();

	ClosePopup();	
}

void UPopupSettlerSchedule::ClosePopup()
{
	PlayerController->UIController->RemovePopup(EPopup::SettlerSchedule);
}

void UPopupSettlerSchedule::HandleSliderChangedFun(float InValue)
{
	HandleSteps(ESlider::Fun, InValue);
	
}
void UPopupSettlerSchedule::HandleSliderChangeWork(float InValue)
{
	HandleSteps(ESlider::Work, InValue);

}
void UPopupSettlerSchedule::HandleSliderChangedSleep(float InValue)
{
	HandleSteps(ESlider::Sleep, InValue);

}

void UPopupSettlerSchedule::HandleSteps(ESlider Slider,float InValue)
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