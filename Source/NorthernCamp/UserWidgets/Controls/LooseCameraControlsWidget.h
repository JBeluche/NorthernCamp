// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LooseCameraControlsWidget.generated.h"

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
	class UButton* ButtonWill;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonTrader;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TB_Clock;

	FTimerHandle UpdateClockTimerHandle;
	void SetClock();

	ADayNightActorController* DayNightController;
	
	UFUNCTION()
	void SwitchToCamp();

	UFUNCTION()
	void SwitchToWill();

	UFUNCTION()
	void SwitchToTrader();
	UFUNCTION()
	void SwitchToHunter();
	UFUNCTION()
	void SwitchToSeaclan();
	UFUNCTION()
	void SwitchToMinedweler();
	UFUNCTION()
	void SwitchToDruida();
	UFUNCTION()
	void SwitchToAlchemist();
	UFUNCTION()
	void SwitchToOccultist();

	ANorthernCampPlayerController* PlayerController;
};
