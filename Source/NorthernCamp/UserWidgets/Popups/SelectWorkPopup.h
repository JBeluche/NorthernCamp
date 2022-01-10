// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "NorthernCamp/Controllers/ResourceController.h"
#include "SelectWorkPopup.generated.h"

class ANorthernCampPlayerController;
class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API USelectWorkPopup : public UUserWidget
{
	GENERATED_BODY()
	
private:
	virtual bool Initialize();
	virtual void NativeConstruct();
	void AddGatherResourceButtons();
	void AddBuildingsWithWorkButtons();


	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* UGP_GatherResource;
	
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* UGP_WorkBuilding;

	UPROPERTY(meta = (BindWidget))
	UButton* B_QuitPopup;

	ANorthernCampPlayerController* PlayerController;
	UUserWidget* WidgetINeed;
	AResourceController* ResourceController;

	UFUNCTION()
	void Exit();
};
