// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "LooseCameraMainUserWidget.generated.h"


class ANorthernCampPlayerController;


UCLASS()
class NORTHERNCAMP_API ULooseCameraMainUserWidget : public UUserWidget
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


