// Copyright Creating Mountains!


#include "NorthernCamp/Controllers/UIController.h"

#include <stdbool.h>

#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "NorthernCamp/UserWidgets/SettlerInfoUserWidget.h"


// Sets default values for this component's properties
UUIController::UUIController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	//Main constructors
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPControlsLooseCamera(TEXT("/Game/Blueprints/UserWidgets/WBP_LooseCameraMain"));
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPSettlersInfoUserWidget(TEXT("/Game/Blueprints/UserWidgets/WBP_SettlerInfo"));
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPControlsCamp(TEXT("/Game/Blueprints/UserWidgets/WBP_CampCameraControls"));

	//Popup constructors
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPSettlerPopup(TEXT("/Game/Blueprints/UserWidgets/Popups/WBP_SettlerSchedule"));
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPSelectResidence(TEXT("/Game/Blueprints/UserWidgets/Popups/WBP_SelectResidencePopup"));
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPSelectWork(TEXT("/Game/Blueprints/UserWidgets/Popups/WBP_SelectWorkPopup"));
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPAccept(TEXT("/Game/Blueprints/UserWidgets/Popups/WBP_Accept"));

	//Helpers
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPCustomOverlay(TEXT("/Game/Blueprints/UserWidgets/WBP_CustomOverlay"));



	//Main 
	LooseCameraUserWidget = WBPControlsLooseCamera.Class;
	SettlerInfoUserWidget = WBPSettlersInfoUserWidget.Class;
	CampControlClass = WBPControlsCamp.Class;

	//Popups
	SettlerSchedulePopup = WBPSettlerPopup.Class;
	SelectWorkPopup = WBPSelectWork.Class;
	SelectResidencePopup = WBPSelectResidence.Class;
	AcceptPopup = WBPAccept.Class;

	//Helpers
	CustomOverlay = WBPCustomOverlay.Class;

	//Small elements
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPSelectBuildingIcons(TEXT("/Game/Blueprints/UserWidgets/SmallElements/WBP_SelectBuildingIcons"));
	SelectBuildingIcons = WBPSelectBuildingIcons.Class;
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPButtonGatherResource(TEXT("/Game/Blueprints/UserWidgets/SmallElements/WBP_SelectWorkFind"));
	ButtonGatherResource = WBPButtonGatherResource.Class;
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPButtonWorkBuilding(TEXT("/Game/Blueprints/UserWidgets/SmallElements/WBP_SelectWorkBuilding"));
	ButtonWorkBuilding = WBPButtonWorkBuilding.Class;


	
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

	if(PlayerController)
	{

		//Make it go slower so you can reset the settings?

		if(MainUI){MainUI->RemoveFromViewport();}
		bIsInMenu = false;
		CurrentScrollBar = nullptr;
		if(NewCurrentUI == ECurrentUI::SettlerInfo)
		{
			MainUI = CreateWidget<UUserWidget>(PlayerController, SettlerInfoUserWidget, FName("Settler Information Widget"));
			CurrentScrollBar = Cast<UScrollBox>(Cast<USettlerInfoUserWidget>(MainUI)->ScrollboxWholeWindow);
			bIsInMenu = true;


		}
		else if(NewCurrentUI == ECurrentUI::LooseCamera)
		{
			MainUI = CreateWidget<UUserWidget>(PlayerController, LooseCameraUserWidget, FName("Main Loose Camera Main UI"));
		}
		else if(NewCurrentUI == ECurrentUI::Camp)
		{
			MainUI = CreateWidget<UUserWidget>(PlayerController, CampControlClass, FName("Camp Main UI"));
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

	Overlay = CreateWidget<UUserWidget>(PlayerController, CustomOverlay, FName("Overlay for popups"));
	Overlay->AddToViewport();

	
	if(NewPopup == EPopup::SettlerSchedule)
	{
		Popup = CreateWidget<UUserWidget>(PlayerController, SettlerSchedulePopup, FName("Select schedule popup"));
	}
	else if(NewPopup == EPopup::SelectWork)
	{
		Popup = CreateWidget<UUserWidget>(PlayerController, SelectWorkPopup, FName("Select work popup"));
	}
	
	else if(NewPopup == EPopup::SelectResidence)
	{
		Popup = CreateWidget<UUserWidget>(PlayerController, SelectResidencePopup, FName("Select residence popup"));
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
		Popup->Destruct();
		PlayerController->ResetControlls();
		if(MainUI)
		{
			MainUI->bIsEnabled = true;
		}
	}
}

