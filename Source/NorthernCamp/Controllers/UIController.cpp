// Copyright Creating Mountains!


#include "NorthernCamp/Controllers/UIController.h"

#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "NorthernCamp/UserWidgets/SettlerInformations/SettlerInformationWidget.h"


// Sets default values for this component's properties
UUIController::UUIController()
{
	PrimaryComponentTick.bCanEverTick = false;

	//-----------------------------------
	// Class finders
	//-----------------------------------
	
	//Controls
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPLooseCameraControlsWidget(TEXT("/Game/Blueprints/UserWidgets/Controls/WBP_LooseCameraControlsWidget"));
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPCampCameraControlsWidget(TEXT("/Game/Blueprints/UserWidgets/Controls/WBP_CampCameraControlsWidget"));
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPBattleCameraControlsWidget(TEXT("/Game/Blueprints/UserWidgets/Controls/WBP_BattleCameraControlsWidget"));


	//Settler informations
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPSettlerInformationWidget(TEXT("/Game/Blueprints/UserWidgets/SettlerInformation/WBP_SettlerInformationWidget"));

	//Settler informations -> Popus
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPScheduleSettingsWidget(TEXT("/Game/Blueprints/UserWidgets/SettlerInformation/Popups/WBP_ScheduleSettingsWidget"));
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPSelectResidenceWidget(TEXT("/Game/Blueprints/UserWidgets/SettlerInformation/Popups/WBP_SelectResidenceWidget"));
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPSelectWorkWidget(TEXT("/Game/Blueprints/UserWidgets/SettlerInformation/Popups/WBP_SelectWorkWidget"));
	
	//Settler informations -> Entries
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPWorkplaceEntryWidget(TEXT("/Game/Blueprints/UserWidgets/SettlerInformation/Entries/WBP_WorkplaceEntryWidget"));
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPResidenceEntryWidget(TEXT("/Game/Blueprints/UserWidgets/SettlerInformation/Entries/WBP_ResidenceEntryWidget"));
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPGatherTaskEntryWidget(TEXT("/Game/Blueprints/UserWidgets/SettlerInformation/Entries/WBP_GatherTaskEntryWidget"));
	
	//Universal

	//Universal -> Popups
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPConfirmationPopupWidget(TEXT("/Game/Blueprints/UserWidgets/Universal/Popups/WBP_ConfirmationPopupWidget"));

	//Universal -> Components
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPBlackOverlayWidget(TEXT("/Game/Blueprints/UserWidgets/Universal/Components/WBP_BlackOverlayWidget"));



	//-----------------------------------
	// Setup classes
	//-----------------------------------
	
	//Controls
	LooseCameraControlsWidget = WBPLooseCameraControlsWidget.Class;
	CampCameraControlsWidget = WBPCampCameraControlsWidget.Class;
	BattleCameraControlsWidget = WBPBattleCameraControlsWidget.Class;

	//Settler informations
	SettlerInformationWidget = WBPSettlerInformationWidget.Class;
	
	//Settler informations -> Popus
	ScheduleSettingsWidget = WBPScheduleSettingsWidget.Class;
	SelectResidenceWidget = WBPSelectResidenceWidget.Class;
	SelectWorkWidget = WBPSelectWorkWidget.Class;

	//Settler informations -> Entries
	WorkplaceEntryWidget = WBPWorkplaceEntryWidget.Class;
	ResidenceEntryWidget = WBPResidenceEntryWidget.Class;
	GatherTaskEntryWidget = WBPGatherTaskEntryWidget.Class;
	
	//Universal

	//Universal -> Popups
	ConfirmationPopupWidget = WBPConfirmationPopupWidget.Class;

	//Universal -> Components
	BlackOverlayWidget = WBPBlackOverlayWidget.Class;



}
// Called when the game starts
void UUIController::BeginPlay()
{
	Super::BeginPlay();
}

void UUIController::UpdateUI(ECurrentUI NewCurrentUI)
{
	
	PlayerController = Cast<ANorthernCampPlayerController>(GetOwner());
	CurrentUI = NewCurrentUI;

	if (PlayerController)
	{
		if (MainUI) { MainUI->RemoveFromViewport(); }
		bIsInMenu = false;
		CurrentScrollBar = nullptr;
		if (NewCurrentUI == ECurrentUI::SettlerInfo)
		{
			MainUI = CreateWidget<UUserWidget>(PlayerController, SettlerInformationWidget, FName("Settler Information Widget"));
			CurrentScrollBar = Cast<UScrollBox>(Cast<USettlerInformationWidget>(MainUI)->ScrollboxWholeWindow);
			bIsInMenu = true;
		}
		else if (NewCurrentUI == ECurrentUI::LooseCamera)
		{
			MainUI = CreateWidget<UUserWidget>(PlayerController, LooseCameraControlsWidget, FName("Main Loose Camera Main UI"));
		}
		else if (NewCurrentUI == ECurrentUI::Camp)
		{
			MainUI = CreateWidget<UUserWidget>(PlayerController, CampCameraControlsWidget, FName("Camp Main UI"));
		}


		MainUI->AddToViewport();
		PlayerController->ResetControlls();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cast failed for player controller in UI Controller"));
	}
}
void UUIController::DisplayPopup(EPopup NewPopup)
{

	Overlay = CreateWidget<UUserWidget>(PlayerController, BlackOverlayWidget, FName("Overlay for popups"));
	Overlay->AddToViewport();

	if(NewPopup == EPopup::SettlerSchedule)
	{
		Popup = CreateWidget<UUserWidget>(PlayerController, ScheduleSettingsWidget, FName("Select schedule popup"));
	}
	else if(NewPopup == EPopup::SelectWork)
	{
		Popup = CreateWidget<UUserWidget>(PlayerController, SelectWorkWidget, FName("Select work popup"));
	}
	
	else if(NewPopup == EPopup::SelectResidence)
	{
		Popup = CreateWidget<UUserWidget>(PlayerController, SelectResidenceWidget, FName("Select residence popup"));
	}
	
	bIsInMenu = true;
	bScrollingEnabled = false;

	Popup->AddToViewport();
}

void UUIController::RemovePopup(EPopup PopupToRemove)
{
	Overlay->RemoveFromViewport();
	PlayerController->ResetControlls();
	
	
	if(Popup)
	{
		Popup->RemoveFromViewport();
		//Popup->Destruct();
		PlayerController->ResetControlls();
		if(MainUI)
		{
			MainUI->bIsEnabled = true;
		}
	}
}

