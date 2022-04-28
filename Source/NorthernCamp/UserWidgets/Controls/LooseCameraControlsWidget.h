// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NorthernCamp/Actors/CartBaseActor.h"
#include "LooseCameraControlsWidget.generated.h"

class UUniformGridPanel;
class ANorthernCampPlayerController;
class ADayNightActorController;
/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API ULooseCameraControlsWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize();

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* CampView;



	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TB_Clock;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* UGP_ResoucesTotal;

	FTimerHandle UpdateClockTimerHandle;
	void SetClock();

	ADayNightActorController* DayNightController;
	
	UFUNCTION()
	void SwitchToCamp();

	ANorthernCampPlayerController* PlayerController;
	UUserWidget* EntryWidget;
	UUserWidget* ResourceEntryWidget;

public:
	void UpdateResoucesAmountDisplayed();

};
