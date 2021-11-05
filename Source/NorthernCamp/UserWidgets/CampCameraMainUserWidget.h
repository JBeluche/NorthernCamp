// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CampCameraMainUserWidget.generated.h"

class ANorthernCampPlayerController;

UCLASS()
class NORTHERNCAMP_API UCampCameraMainUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SwitchToCharacter();
	
	
	UPROPERTY(meta = (BindWidget))
	class UButton* B_SwitchToLoosCameraPawn;

	ANorthernCampPlayerController* PlayerController;
	

};
