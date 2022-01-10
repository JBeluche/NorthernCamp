// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/Image.h"
#include "NorthernCamp/NorthernCampPlayerController.h"
#include "NorthernCamp/Characters/CharacterSettler.h"
#include "SelectBuildingButtons.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API USelectBuildingButtons : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual bool Initialize();
	UUserWidget* AcceptPopupWidget;
	ANorthernCampPlayerController* PlayerController;


public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TX_BuildingName;

	UPROPERTY(meta = (BindWidget))
	UImage* IMG_BuildingIcon;

	UPROPERTY(meta = (BindWidget))
	UButton* B_ThisSelected;
	
	UPROPERTY(meta = (BindWidget))
	UImage* IMG_CheckedOverlay;

	bool bIsSelected;

	ABuildingBaseActor* Building;

	UFUNCTION()
	void Selected();

	UFUNCTION()
	void Accepted();
};
