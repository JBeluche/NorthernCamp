// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NorthernCamp/Characters/CharacterSettler.h"
#include "PopupSettlerSchedule.generated.h"

class UTextBlock;
class ANorthernCampPlayerController;
class USlider;
class UButton;


UENUM(Blueprintable)
enum class ESlider : uint8
{
	Fun UMETA(DisplayName = "Fun"),
	Work UMETA(DisplayName = "Work"),
	Sleep UMETA(DisplayName = "Sleep"),

};


UCLASS()
class NORTHERNCAMP_API UPopupSettlerSchedule : public UUserWidget
{
	GENERATED_BODY()

	
private:
	virtual bool Initialize();

	UPROPERTY(meta = (BindWidget))
	UButton* B_Cancel;

	UPROPERTY(meta = (BindWidget))
	UButton* B_Accept;

	UPROPERTY(meta = (BindWidget))
	USlider* Slider_Work;

	UPROPERTY(meta = (BindWidget))
	USlider* Slider_Sleep;

	UPROPERTY(meta = (BindWidget))
	USlider* Slider_Fun;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_SleepHours;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_FunHours;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_WorkHours;


	ACharacterSettler* Settler;
	ANorthernCampPlayerController* PlayerController;


	//Private functions
	UFUNCTION()
	void HandleSliderChangedFun(float InValue);
	
	UFUNCTION()
	void HandleSliderChangeWork(float InValue);
	
	UFUNCTION()
	void HandleSliderChangedSleep(float InValue);

	UFUNCTION()
	void SaveSchedule();

	UFUNCTION()
	void ClosePopup();
	
	void HandleSteps(ESlider Slider,float InValue);
	
};
