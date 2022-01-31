// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UIController.generated.h"


class ANorthernCampPlayerController;
class UScrollBox;
UENUM(BlueprintType)
enum class ECurrentUI : uint8 
{
	SettlerInfo UMETA(DisplayName = "Information Settler"),
	LooseCamera UMETA(DisplayName = "Loose Camera"),
	Camp UMETA(DisplayName = "Camp UI"),
};

UENUM(BlueprintType)
enum class EPopup : uint8 
{
	SettlerSchedule UMETA(DisplayName = "Settler Schedule"),
	SelectResidence UMETA(DisplayName = "Select Residence"),
	SelectWork UMETA(DisplayName = "Select Work"),
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NORTHERNCAMP_API UUIController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUIController();
	
	void UpdateUI(ECurrentUI NewCurrentUI);
	void DisplayPopup(EPopup NewPopup);
	void RemovePopup(EPopup PopupToRemove);

	//Public variables
	bool bIsInMenu;
	bool bScrollingEnabled = true;
	UScrollBox* CurrentScrollBar;

	
	TSubclassOf<class UUserWidget> ConfirmationPopupWidget;

	TSubclassOf<class UUserWidget> WorkplaceEntryWidget;
	TSubclassOf<class UUserWidget> ResidenceEntryWidget;
	TSubclassOf<class UUserWidget> GatherTaskEntryWidget;
	TSubclassOf<class UUserWidget> ResourceCounterEntryWidget;

	TSubclassOf<class UUserWidget> LooseCameraControlsWidget;

	UUserWidget* MainUI;
	UUserWidget* Overlay;
	UUserWidget* Popup;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Protected Varaibles 
	TSubclassOf<class UUserWidget> CampCameraControlsWidget;
	TSubclassOf<class UUserWidget> BattleCameraControlsWidget;

	TSubclassOf<class UUserWidget> SettlerInformationWidget;

	TSubclassOf<class UUserWidget> ScheduleSettingsWidget;
	TSubclassOf<class UUserWidget> SelectResidenceWidget;
	TSubclassOf<class UUserWidget> SelectWorkWidget;

	TSubclassOf<class UUserWidget> BlackOverlayWidget;



	TSubclassOf<class UUserWidget> DialogWidget;


	ECurrentUI CurrentUI = ECurrentUI::LooseCamera;

	ANorthernCampPlayerController* PlayerController;
		
};
