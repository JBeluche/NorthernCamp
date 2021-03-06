// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResidenceEntryWidget.generated.h"

class ABuildingBaseActor;
class UButton;
class UImage;
class UTextBlock;
class ANorthernCampPlayerController;
/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UResidenceEntryWidget : public UUserWidget
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

