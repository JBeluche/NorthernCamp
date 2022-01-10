// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "SettlerInformationWidget.generated.h"

class ACharacterSettler;
class UVitalsComponent;
class UButton;
class UProgressBar;
class UScrollBox;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API USettlerInformationWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	virtual bool Initialize();

	void UpdateInfoSettler();

	FTimerHandle UpdateInfoSettlerTimerHandle;
	ACharacterSettler* Settler;

	UVitalsComponent* CharacterVitalsComponent;
	
	ANorthernCampPlayerController* PlayerController;

	UPROPERTY(meta = (BindWidget))
	UButton* B_BackButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* B_TimeManager;

	UPROPERTY(meta = (BindWidget))
	UButton* B_SetResidence;

	UPROPERTY(meta = (BindWidget))
	UButton* B_SetWork;
	
	UFUNCTION()
	void ExitInfoPanel();

	UFUNCTION()
	void OpenScheduleSettler();

	UFUNCTION()
	void OpenSelectWorkPopup();

	UFUNCTION()
	void OpenSelectResidencePopup();

public:
	//virtual void NativeConstruct() override;

	//Basic information settler
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_SettlersName;

	//Vitals settler
	UPROPERTY(meta = (BindWidget))
	UProgressBar* PB_HealthMeter;
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* PB_WaterMeter;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* PB_FoodMeter;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* PB_SleepMeter;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* PB_FunFireMeter;

	//Main functions widget
	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollboxWholeWindow;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_Work;
	
	UPROPERTY(meta = (BindWidget))
	UImage* IMG_Work;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_Residence;
	
	UPROPERTY(meta = (BindWidget))
	UImage* IMG_Residence;

	void RefreshSettlerInfo();

};
