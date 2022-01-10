// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectWorkBuilding.generated.h"

class UButton;
class ABuildingBaseActor;
class UImage;
class UTextBlock;
class ANorthernCampPlayerController;
/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API USelectWorkBuilding : public UUserWidget
{
	GENERATED_BODY()
	
	
private:
	virtual bool Initialize();
	UUserWidget* AcceptPopupWidget;
	ANorthernCampPlayerController* PlayerController;


public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TX_Name;

	UPROPERTY(meta = (BindWidget))
	UImage* IMG_Icon;
	
	ABuildingBaseActor* Building;

	UPROPERTY(meta = (BindWidget))
	UButton* B_ThisSelected;
	
	UFUNCTION()
	void Selected();

	UFUNCTION()
	void Accepted();	
};
