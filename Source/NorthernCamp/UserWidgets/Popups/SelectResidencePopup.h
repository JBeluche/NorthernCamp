// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectResidencePopup.generated.h"

class UButton;
class ANorthernCampPlayerController;
class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API USelectResidencePopup : public UUserWidget
{
	GENERATED_BODY()


	
private:
	virtual bool Initialize();
	virtual void NativeConstruct();

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* UGP_BuildingIcons;

	ANorthernCampPlayerController* PlayerController;
	UUserWidget* WidgetINeed;
	
	UPROPERTY(meta = (BindWidget))
	UButton* B_QuitPopup;

	UFUNCTION()
	void Exit();

};
