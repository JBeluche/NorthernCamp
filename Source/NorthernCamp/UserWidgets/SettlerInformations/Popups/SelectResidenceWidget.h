// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectResidenceWidget.generated.h"

class UButton;
class ANorthernCampPlayerController;
class UUniformGridPanel;

UCLASS()
class NORTHERNCAMP_API USelectResidenceWidget : public UUserWidget
{
	GENERATED_BODY()


private:
	virtual bool Initialize();
	virtual void NativeConstruct();

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* UGP_BuildingIcons;

	ANorthernCampPlayerController* PlayerController;
	UUserWidget* WidgetINeed;
	UUserWidget* AcceptPopupWidget;

	UPROPERTY(meta = (BindWidget))
	UButton* B_QuitPopup;
	
	UPROPERTY(meta = (BindWidget))
	UButton* B_Clear;
	
	UFUNCTION()
	void Exit();

	UFUNCTION()
	void OpenAcceptPopup();

	UFUNCTION()
	void ClearResidence();
};
